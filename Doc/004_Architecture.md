# Chapter 4: Kiến trúc ARM Cortex-M4

Chương này tập trung vào các kiến thức nền tảng của vi điều khiển ARM Cortex-M4. Đây là những nội dung cơ bản nhưng rất quan trọng, cần nắm vững trước khi tiếp cận các chương sau.

Bộ xử lý Cortex-M3 và Cortex-M4 được xây dựng dựa trên kiến trúc **ARMv7-M**. Trong đó, các đặc điểm của **ARMv7-M** và phần mở rộng **ARMv7E-M** đều được mô tả trong cùng một tài liệu kiến trúc là **ARMv7-M Architecture Reference Manual**.

Phạm vi của chương này không đi sâu vào toàn bộ tài liệu kiến trúc, mà chỉ tập trung vào những khái niệm cốt lõi cần thiết để hiểu cách hoạt động của core Cortex-M4 từ góc nhìn của người phát triển phần mềm.

## Programmer’s model

### 4.2.1 Operation modes and states

Trên ARM Cortex-M4, cần phân biệt rõ ba khái niệm:

- **Operation states**: trạng thái hoạt động của bộ xử lý
- **Operation modes**: chế độ thực thi của bộ xử lý
- **Access levels**: mức đặc quyền khi thực thi mã lệnh

Các trạng thái và chế độ này được mô tả trong hình sau:

![ARM-STATE](https://github.com/DukeChan74/Doc-M4/blob/main/picture/004/coreMode.png?raw=true)

Có thể tóm tắt như sau.

#### Operation states

- **Debug state**: Khi bộ xử lý bị dừng bởi debugger, hoặc khi gặp breakpoint, nó đi vào trạng thái debug và tạm dừng thực thi lệnh.
- **Thumb state**: Khi bộ xử lý đang thực thi mã chương trình, nó hoạt động ở trạng thái Thumb. Khác với các bộ xử lý ARM cổ điển như ARM7TDMI, Cortex-M không hỗ trợ tập lệnh ARM nên không tồn tại ARM state.

#### Operation modes

- **Handler mode**: Đây là chế độ khi bộ xử lý đang xử lý ngoại lệ, ví dụ như ngắt hoặc fault exception. Mọi mã lệnh chạy trong Handler mode đều ở mức **privileged**.
- **Thread mode**: Đây là chế độ khi bộ xử lý thực thi mã ứng dụng thông thường. Trong Thread mode, bộ xử lý có thể chạy ở mức **privileged** hoặc **unprivileged**.

#### Access levels

- **Privileged**: Có quyền truy cập đầy đủ tới các tài nguyên của hệ thống, bao gồm các thanh ghi điều khiển hệ thống và các thao tác đặc biệt.
- **Unprivileged**: Bị giới hạn quyền truy cập. Một số vùng nhớ, thanh ghi hệ thống và thao tác đặc biệt sẽ không thể sử dụng trực tiếp.

Điểm quan trọng cần lưu ý là **Thread mode** và **Handler mode** là **chế độ thực thi**, còn **privileged** và **unprivileged** là **mức đặc quyền truy cập**. Đây là hai khái niệm khác nhau và không nên nhầm lẫn.

### Chuyển từ privileged sang unprivileged

Trong Thread mode, phần mềm có thể chủ động hạ quyền từ **privileged** xuống **unprivileged** bằng cách thiết lập bit `nPRIV` trong thanh ghi **CONTROL**.

Việc này thường được sử dụng khi hệ thống muốn tách mã ứng dụng thông thường ra khỏi phần mềm lõi của hệ thống, chẳng hạn như kernel của RTOS.

### Vì sao không thể tự chuyển ngược lại?

Một đoạn mã đang chạy ở **unprivileged Thread mode** không thể tự nâng quyền trở lại **privileged Thread mode**. Nguyên nhân là vì thao tác thay đổi bit `nPRIV` trong thanh ghi **CONTROL** chỉ được phép thực hiện khi bộ xử lý đang ở mức đặc quyền.

Nói cách khác, khi đã ở unprivileged, phần mềm không còn quyền tự sửa `CONTROL` để nâng quyền cho chính nó.

Đây là cơ chế quan trọng nhằm ngăn không cho mã ứng dụng tự ý chiếm quyền điều khiển toàn bộ hệ thống.

### Vai trò của SVC trong việc nâng quyền

Để quay từ **unprivileged Thread mode** về **privileged Thread mode**, bộ xử lý phải sử dụng cơ chế ngoại lệ. Cách phổ biến nhất là sử dụng ngoại lệ **SVC (Supervisor Call)**.

Quá trình này diễn ra theo trình tự sau:

1. Ứng dụng đang chạy ở **unprivileged Thread mode** không thể tự ghi vào thanh ghi **CONTROL**.
2. Ứng dụng thực thi lệnh **SVC** để yêu cầu một dịch vụ hệ thống.
3. Lệnh này kích hoạt ngoại lệ **SVC**, khiến bộ xử lý chuyển sang **Handler mode**.
4. Vì **Handler mode** luôn chạy ở mức **privileged**, hàm phục vụ `SVC_Handler()` có thể thực hiện các thao tác nhạy cảm, ví dụ như thay đổi lại thanh ghi **CONTROL**.
5. Khi thoát khỏi exception handler, bộ xử lý quay lại **Thread mode** với mức đặc quyền đã được cập nhật.

Hình dưới đây minh họa mối quan hệ giữa các mức đặc quyền:

![AccessLevel](https://github.com/DukeChan74/Doc-M4/blob/main/picture/004/AccessLevel.png?raw=true)

Code demo: [003_operation_modes](https://github.com/DukeChan74/Doc-M4/tree/main/Code/003_operation_modes)

Đoạn code trên minh họa rằng một chương trình đang chạy ở **unprivileged Thread mode** không thể tự ý quay trở lại **privileged Thread mode** nếu không thông qua cơ chế exception. Để thực hiện việc chuyển quyền theo chiều ngược lại, có thể sử dụng cơ chế **SVC** như trong ví dụ dưới đây:

![SwitchMode](https://github.com/DukeChan74/Doc-M4/blob/main/picture/004/SVC_switchmode.png?raw=true)

### Ý nghĩa của cơ chế phân quyền

Thoạt nhìn, việc phân tách **privileged** và **unprivileged** có vẻ làm hệ thống trở nên phức tạp hơn. Tuy nhiên, đây là một cơ chế rất quan trọng, đặc biệt khi kết hợp với **MPU (Memory Protection Unit)**.

Việc phân quyền này mang lại một số lợi ích chính:

- Bảo vệ vùng nhớ quan trọng của hệ thống
- Ngăn mã ứng dụng truy cập trực tiếp vào các tài nguyên nhạy cảm
- Hạn chế khả năng một tác vụ lỗi làm ảnh hưởng tới toàn bộ hệ thống
- Tạo nền tảng để xây dựng mô hình kernel/user trong RTOS

Trong một hệ điều hành nhúng, mô hình phổ biến là:

- **Kernel** chạy ở mức **privileged**
- **Application tasks** chạy ở mức **unprivileged**

Khi đó, các tác vụ ứng dụng muốn thực hiện những thao tác nhạy cảm như:

- cấp phát tài nguyên hệ thống
- thay đổi cấu hình timer hệ thống
- tác động tới scheduler
- truy cập vùng nhớ dùng chung đặc biệt

thì không được thực hiện trực tiếp, mà phải thông qua **system service** do kernel cung cấp, thường được gọi qua cơ chế **SVC**.

Nhờ đó, RTOS có thể quản lý tài nguyên theo cách tập trung, có kiểm soát và an toàn hơn. Đây cũng là nền tảng quan trọng để nâng cao độ ổn định và độ tin cậy của hệ thống nhúng.

Nội dung này sẽ còn được đề cập chi tiết hơn trong các phần liên quan tới RTOS và các chương sau.