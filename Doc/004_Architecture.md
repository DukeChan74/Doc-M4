# Chapter 4: Kiến trúc ARM CORTEX M4

Chương này tập trung vào kiến thức nền, bắt buộc phải đọc chương này để nắm được cơ bản để hiểu những chương sau này.

Bộ xử lý Cortex-M3 và Cortex-M4 được xây dựng dựa trên kiến trúc ARMv7-M. Cả các đặc điểm của ARMv7-M và ARMv7E-M đều được tài liệu hóa trong cùng một tài liệu đặc tả kiến trúc: ARMv7-M Architecture Reference Manual.

Trong chương này tôi sẽ viết những điều cơ bản nhất và cần biết nhất khi học về core. 

## Programmer’s model

### 4.2.1 Operation modes and states

Arm cortex M4 chia chia trạng thái hoạt động thành 2 Operation states và Operation modes. Các trạng thái được mô tả dưới hình sau:

![ARM-STATE](https://github.com/DukeChan74/Doc-M4/blob/main/picture/004/coreMode.png)

Tóm gọn lại nó là như này:

**Operation states**
- **Debug state**: Khi bộ xử lý bị dừng lại (ví dụ do trình gỡ lỗi can thiệp hoặc sau khi gặp một điểm dừng breakpoint), nó sẽ chuyển vào trạng thái gỡ lỗi và ngừng thực thi lệnh.
- **Thumb state**: Khi bộ xử lý đang chạy mã chương trình (các lệnh Thumb), nó ở trong trạng thái Thumb. Khác với các bộ xử lý ARM cổ điển như ARM7TDMI, ở đây không có trạng thái ARM, vì các bộ xử lý Cortex-M không hỗ trợ tập lệnh ARM.

**Operation modes**

- **Chế độ Handler (Handler mode)**: Đây là chế độ khi bộ xử lý đang thực thi một trình xử lý ngoại lệ, chẳng hạn như trình phục vụ ngắt (Interrupt Service Routine - ISR). Khi ở chế độ Handler, bộ xử lý luôn có mức truy cập đặc quyền (privileged access level).

- **Chế độ Thread (Thread mode)**: Đây là chế độ khi bộ xử lý đang thực thi mã ứng dụng thông thường. Trong chế độ này, bộ xử lý có thể hoạt động ở mức truy cập đặc quyền (privileged) hoặc không đặc quyền (unprivileged). Việc này được điều khiển bởi một thanh ghi đặc biệt có tên là CONTROL. Nội dung này sẽ được trình bày chi tiết hơn trong mục 4.2.3.

Phần mềm có thể chuyển bộ xử lý từ **Thread mode** có đặc quyền **(privileged Thread mode)** sang Thread mode không đặc quyền **(unprivileged Thread mode)**. Tuy nhiên, nó không thể tự chuyển ngược lại từ unprivileged về privileged. Nếu cần thực hiện việc này, bộ xử lý phải sử dụng cơ chế ngoại lệ (exception mechanism) để xử lý quá trình chuyển đổi.

Lý do chỉ có một chiều đó là: chỉ khi tác động vào thanh ghi CONTROL mới có thể chuyển mode, mà thanh ghi CONTROL chỉ được phép ghi khi ở **privileged**. Do đó ngoại lệ **SVC** sinh ra như một ngắt vượt quyền. Cụ thể nó sẽ thực hiện như sau: 
- Ứng dụng đang chạy ở unprivileged Thread mode không thể tự ghi vào thanh ghi CONTROL để quay lại privileged.

- Thay vào đó, ứng dụng sẽ thực thi lệnh SVC.

- Lệnh này kích hoạt ngoại lệ SVC, làm bộ xử lý chuyển sang Handler mode.

- Mà Handler mode luôn chạy ở privileged level, nên bên trong hàm phục vụ SVC, hệ điều hành hoặc phần mềm đặc quyền có thể thực hiện việc nâng quyền hoặc xử lý yêu cầu cần thiết (Ví dụ sửa CONTROL để quay lại privilege).

