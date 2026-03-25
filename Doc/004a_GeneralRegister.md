# Chapter 4: Kiến trúc ARM Cortex-M4

Bài viết này tập trung vào mô tả các thanh ghi chung trong arm cortex M4.

Tương tự như hầu hết các bộ xử lý khác, bộ xử lý  **Cortex-M4** có một số **thanh ghi** bên trong lõi xử lý để thực hiện việc xử lý dữ liệu và điều khiển. Phần lớn các thanh ghi này được nhóm lại trong một khối gọi là **register bank**.

Mỗi lệnh xử lý dữ liệu sẽ chỉ rõ:

- phép toán cần thực hiện,
- thanh ghi nguồn,
- và thanh ghi đích, nếu có.

Trong kiến trúc **ARM**, nếu dữ liệu nằm trong bộ nhớ mà cần được xử lý, thì dữ liệu đó phải được **nạp từ bộ nhớ vào các thanh ghi** trong register bank, sau đó được xử lý bên trong bộ xử lý, và cuối cùng, nếu cần, sẽ được **ghi trở lại bộ nhớ**. Mô hình này thường được gọi là **kiến trúc load-store**.

Tương tự như hầu hết các bộ xử lý khác, bộ xử lý **Cortex-M3** và **Cortex-M4** có một số **thanh ghi** bên trong lõi xử lý để thực hiện việc xử lý dữ liệu và điều khiển. Phần lớn các thanh ghi này được nhóm lại trong một khối gọi là **register bank**.

Mỗi lệnh xử lý dữ liệu sẽ chỉ rõ:

- phép toán cần thực hiện,
- thanh ghi nguồn,
- và thanh ghi đích, nếu có.

Trong kiến trúc **ARM**, nếu dữ liệu nằm trong bộ nhớ mà cần được xử lý, thì dữ liệu đó phải được **nạp từ bộ nhớ vào các thanh ghi** trong register bank, sau đó được xử lý bên trong bộ xử lý, và cuối cùng, nếu cần, sẽ được **ghi trở lại bộ nhớ**. Mô hình này thường được gọi là **kiến trúc load-store**.

Có thể hình dung bộ nhớ và thanh ghi theo cách đơn giản như sau:

- **RAM** giống như một kho chứa dữ liệu lớn
- **Thanh ghi** giống như mặt bàn làm việc ngay trước bộ xử lý

Dữ liệu vẫn được lưu trong RAM, nhưng khi cần tính toán, bộ xử lý sẽ không làm việc trực tiếp nhiều lần với RAM. Thay vào đó, nó sẽ lấy dữ liệu từ bộ nhớ đưa vào các thanh ghi, thực hiện xử lý tại đó, sau đó chỉ ghi kết quả trở lại bộ nhớ khi thực sự cần thiết.

Ví dụ, giả sử ta có đoạn mã C sau:

```c
a = b + c;
````
Về bản chất, bộ xử lý sẽ không cộng trực tiếp giá trị của b và c ngay trong RAM. Quá trình xử lý có thể được hiểu theo các bước như sau:

- Đọc giá trị của b từ bộ nhớ vào một thanh ghi

- Đọc giá trị của c từ bộ nhớ vào một thanh ghi khác

- Thực hiện phép cộng trong core

- Lưu kết quả vào một thanh ghi đích

- Nếu cần, ghi kết quả từ thanh ghi trở lại bộ nhớ để cập nhật cho biến a

Để dễ hiểu hơn quan sát đoạn ASM sau:
```s
LDR R0, [b]     ; nạp b từ bộ nhớ vào thanh ghi R0
LDR R1, [c]     ; nạp c từ bộ nhớ vào thanh ghi R1
ADD R2, R0, R1  ; cộng R0 và R1, lưu kết quả vào R2
STR R2, [a]     ; ghi kết quả từ R2 ra bộ nhớ
```

Chính vì vậy, **register bank** có vai trò rất quan trọng trong kiến trúc ARM. Nó là vùng làm việc trung gian có tốc độ cao giữa lõi xử lý và bộ nhớ, giúp các lệnh xử lý dữ liệu được thực hiện hiệu quả hơn. Đây cũng là một trong những đặc điểm tiêu biểu của kiến trúc **load-store**, nơi việc truy cập bộ nhớ và việc xử lý dữ liệu được tách biệt rõ ràng.


## 4.2.2 Registers

**Register bank** của bộ xử lý **Cortex-M3** và **Cortex-M4** có tổng cộng **16 thanh ghi**. Trong đó:

- **13 thanh ghi** là các **thanh ghi đa dụng 32-bit (general-purpose registers)**,
- và **3 thanh ghi còn lại** được dành cho các **chức năng đặc biệt**,

Tất cả được mô tả dưới hình sau: 

![Registerbank](https://github.com/DukeChan74/Doc-M4/blob/main/picture/004/Registerbank.png?raw=true)

### R0 đến R12

Các thanh ghi từ **R0 đến R12** là các **thanh ghi đa dụng (general-purpose registers)**. Trong đó, **8 thanh ghi đầu tiên (R0 đến R7)** còn được gọi là **low registers**. Do không gian mã lệnh bị giới hạn, nhiều lệnh **16-bit** chỉ có thể truy cập tới các low registers này.

Các **high registers** (**R8 đến R12**) thường được sử dụng với các lệnh **32-bit**, và chỉ có một số ít lệnh **16-bit** có thể truy cập tới chúng, ví dụ như lệnh **MOV**. Giá trị khởi tạo của các thanh ghi từ **R0 đến R12** là **không xác định**.

### R13 - Stack Pointer (SP)

**R13** là **Stack Pointer (SP)**. Thanh ghi này được sử dụng để truy cập vùng nhớ stack thông qua các thao tác **PUSH** và **POP**.

Về mặt phần cứng, thực tế tồn tại **hai Stack Pointer khác nhau**:

- **Main Stack Pointer (MSP)**, hoặc trong một số tài liệu ARM còn được gọi là **SP_main**. Đây là **Stack Pointer mặc định**, được chọn sau khi reset hoặc khi bộ xử lý đang ở **Handler Mode**.
- **Process Stack Pointer (PSP)**, hoặc còn được gọi là **SP_process** trong một số tài liệu ARM. PSP **chỉ có thể được sử dụng trong Thread Mode**.

Việc chọn sử dụng **MSP** hay **PSP** được quyết định bởi một thanh ghi đặc biệt có tên là **CONTROL**, nội dung này sẽ được trình bày ở mục **4.2.3**. Trong các chương trình thông thường, chỉ có **một Stack Pointer** được nhìn thấy tại một thời điểm.

Cả **MSP** và **PSP** đều là các thanh ghi **32-bit**, tuy nhiên **2 bit thấp nhất** của chúng luôn bằng **0**, và mọi thao tác ghi vào hai bit này đều sẽ bị bỏ qua. Trên các bộ xử lý **ARM Cortex-M**, các thao tác **PUSH** và **POP** luôn là **32-bit**, do đó địa chỉ dùng trong các thao tác stack phải được **căn hàng theo biên 32-bit word**.

Trong phần lớn các ứng dụng thông thường, nếu không sử dụng hệ điều hành nhúng (RTOS) thì không nhất thiết phải dùng đến **PSP**. Nhiều ứng dụng đơn giản chỉ cần sử dụng **MSP** là đủ. **PSP** thường được dùng khi có hệ điều hành nhúng, nhằm tách riêng stack của **kernel** và stack của **các tác vụ ứng dụng**.

Giá trị khởi tạo của **PSP** là **không xác định**, còn giá trị khởi tạo của **MSP** được lấy từ **word đầu tiên của bộ nhớ** trong quá trình reset.

### R14 - Link Register (LR)

**R14** còn được gọi là **Link Register (LR)**. Thanh ghi này được dùng để lưu **địa chỉ quay về** khi gọi một hàm hoặc chương trình con.

Khi kết thúc hàm hoặc chương trình con, bộ xử lý có thể quay lại chương trình gọi bằng cách nạp giá trị của **LR** vào **Program Counter (PC)**. Mỗi khi có một lệnh gọi hàm hoặc gọi chương trình con được thực hiện, giá trị của **LR** sẽ được cập nhật tự động.

Nếu một hàm cần gọi tiếp một hàm khác, nó phải **lưu giá trị hiện tại của LR xuống stack** trước. Nếu không, giá trị đang có trong **LR** sẽ bị ghi đè khi lệnh gọi hàm tiếp theo xảy ra.

Trong quá trình xử lý ngoại lệ, **LR** cũng được cập nhật tự động thành một giá trị đặc biệt gọi là **EXC_RETURN (Exception Return)**. Giá trị này được sử dụng để kích hoạt quá trình quay trở lại sau khi kết thúc exception handler. Nội dung này sẽ được trình bày chi tiết hơn trong **Chương 8**.

Mặc dù địa chỉ quay về trên Cortex-M luôn là **địa chỉ chẵn** (bit 0 bằng 0 vì lệnh phải được căn hàng theo địa chỉ half-word), nhưng **bit 0 của LR vẫn có thể đọc và ghi được**. Một số thao tác nhảy hoặc gọi hàm yêu cầu **bit 0 của LR** (hoặc của thanh ghi đang được sử dụng) phải được đặt thành **1** để chỉ ra rằng bộ xử lý đang ở **Thumb state**.

### R15 - Program Counter (PC)

**R15** là **Program Counter (PC)**. Đây là thanh ghi có thể **đọc và ghi** được:

- Khi đọc, giá trị trả về là **địa chỉ của lệnh hiện tại cộng thêm 4**. Điều này xuất phát từ bản chất pipeline của thiết kế, đồng thời nhằm đảm bảo tính tương thích với bộ xử lý **ARM7TDMI**.
- Khi ghi vào **PC** (ví dụ bằng các lệnh xử lý dữ liệu hoặc truyền dữ liệu), thao tác đó sẽ gây ra một **nhánh chương trình (branch)**.

Do các lệnh phải được căn hàng theo địa chỉ **half-word** hoặc **word**, nên **bit thấp nhất (LSB)** của **PC** luôn bằng **0**. Tuy nhiên, khi sử dụng một số lệnh nhảy hoặc lệnh đọc bộ nhớ để cập nhật **PC**, cần phải đặt **LSB của giá trị PC mới bằng 1** để chỉ ra rằng bộ xử lý vẫn đang ở **Thumb state**.

Nếu không làm điều này, bộ xử lý có thể sinh ra **fault exception**, vì nó hiểu rằng chương trình đang cố chuyển sang sử dụng **ARM instruction set** (tập lệnh ARM 32-bit như trên ARM7TDMI), trong khi Cortex-M không hỗ trợ chế độ đó.

Trong các ngôn ngữ lập trình bậc cao như **C** hoặc **C++**, việc thiết lập bit LSB cho địa chỉ nhảy thường được **compiler xử lý tự động**.

Trong đa số trường hợp, thao tác nhảy và gọi hàm được thực hiện bởi các lệnh chuyên dụng cho mục đích này. Việc dùng các lệnh xử lý dữ liệu để cập nhật trực tiếp **PC** là ít phổ biến hơn. Tuy nhiên, giá trị của **PC** rất hữu ích khi truy cập tới các **literal data** được lưu trong bộ nhớ chương trình. Vì vậy, có thể thường xuyên bắt gặp các lệnh đọc bộ nhớ dùng **PC** làm thanh ghi base address, kết hợp với offset được tạo ra bởi các giá trị tức thời trong lệnh.

## 4.2.3 Special registers
PSR, như chính tên gọi của nó, chứa tất cả các cờ trạng thái CPU. 

![xPSR](https://github.com/DukeChan74/Doc-M4/blob/main/picture/004/xPSR.png)

Trong quá trình phát triển các ứng dụng đơn giản bằng ngôn ngữ bậc cao như **C**, số trường hợp cần truy cập trực tiếp tới các thanh ghi này là không nhiều. Tuy nhiên, chúng lại rất quan trọng trong việc phát triển **hệ điều hành nhúng (embedded OS)** hoặc khi cần sử dụng các cơ chế **mask ngắt nâng cao**.

Các **special registers** không được **memory mapped**, vì vậy không thể truy cập theo cách đọc/ghi địa chỉ bộ nhớ như các thanh ghi ngoại vi thông thường. Thay vào đó, chúng được truy cập thông qua các lệnh chuyên dụng như:

```asm
MRS <reg>, <special_reg>   ; đọc special register vào thanh ghi thường
MSR <special_reg>, <reg>   ; ghi từ thanh ghi thường vào special register
```

