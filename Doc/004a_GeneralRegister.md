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

## Registers

### 4.2.2 Registers

![Registerbank](https://github.com/DukeChan74/Doc-M4/blob/main/picture/004/Registerbank.png?raw=true)

