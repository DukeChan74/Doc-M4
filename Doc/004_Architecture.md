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

