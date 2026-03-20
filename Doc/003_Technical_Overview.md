# CHAPTER OUTLINE

## 3.1 Thông tin chung về bộ xử lý Cortex®-M3 và Cortex-M4

### 3.1.1 Loại bộ xử lý

Tất cả các bộ xử lý ARM Cortex-M đều là bộ xử lý **RISC 32-bit** (*Reduced Instruction Set Computing* – máy tính với tập lệnh rút gọn). Các đặc điểm chính của dòng vi xử lý này gồm có:

- Thanh ghi 32-bit
- Đường truyền dữ liệu nội bộ 32-bit
- Giao tiếp bus 32-bit

Ngoài khả năng xử lý dữ liệu 32-bit, các bộ xử lý Cortex-M còn có thể xử lý hiệu quả dữ liệu **8-bit** và **16-bit**. Riêng Cortex-M3 và Cortex-M4 còn hỗ trợ một số phép toán liên quan đến dữ liệu **64-bit**, chẳng hạn như các phép **nhân** và **tích lũy**.

Cortex-M3 và Cortex-M4 đều sử dụng **kiến trúc pipeline 3 giai đoạn**, bao gồm:

1. Nạp lệnh (*instruction fetch*)
2. Giải mã lệnh (*decode*)
3. Thực thi lệnh (*execution*)

Đồng thời, cả hai cũng áp dụng **kiến trúc bus Harvard**, cho phép thực hiện đồng thời việc nạp lệnh và truy cập dữ liệu, từ đó giúp nâng cao hiệu năng xử lý.

Hệ thống nhớ của bộ xử lý ARM Cortex-M sử dụng **địa chỉ hóa 32-bit**, cho phép không gian địa chỉ tối đa lên tới **4 GB**. Bản đồ nhớ của hệ thống là **thống nhất** (*unified memory map*), nghĩa là dù có thể tồn tại nhiều giao tiếp bus khác nhau, toàn bộ hệ thống vẫn chỉ sử dụng một không gian nhớ 4 GB duy nhất. Không gian này được dùng để lưu trữ:

- Mã chương trình
- Dữ liệu
- Ngoại vi
- Một số thành phần hỗ trợ debug bên trong bộ xử lý

Tương tự các bộ xử lý ARM khác, Cortex-M hoạt động theo **kiến trúc load-store**. Điều này có nghĩa là dữ liệu phải được nạp từ bộ nhớ vào thanh ghi, sau đó mới được xử lý, rồi cuối cùng được ghi ngược trở lại bộ nhớ bằng các lệnh riêng biệt.

Ví dụ, để tăng giá trị của một biến đang lưu trong SRAM, bộ xử lý thường thực hiện theo ba bước:

1. Đọc dữ liệu từ SRAM và nạp vào một thanh ghi bên trong bộ xử lý
2. Tăng giá trị trong thanh ghi lên một đơn vị
3. Ghi giá trị mới từ thanh ghi trở lại bộ nhớ

Tập hợp các thanh ghi bên trong bộ xử lý cùng chức năng của chúng thường được gọi là **mô hình lập trình viên** (*programmer’s model*).

### 3.1.2 Kiến trúc bộ xử lý

Bộ xử lý chỉ là một phần của vi điều khiển; còn bộ nhớ, ngoại vi và các giao tiếp khác do nhà sản xuất vi điều khiển tích hợp. Vì vậy, Cortex-M có thể xuất hiện trong nhiều loại thiết bị khác nhau, từ vi điều khiển giá rẻ đến các hệ thống hiệu năng cao, nhưng vẫn dùng chung một nền tảng kiến trúc.

Trong ARM, khái niệm **kiến trúc** thường gồm hai phần:

- **Kiến trúc (Architecture):** bao gồm tập lệnh (ISA), mô hình lập trình viên và cơ chế debug.
- **Vi kiến trúc (Micro-architecture):** bao gồm các chi tiết triển khai như tín hiệu giao tiếp, thời gian thực thi lệnh, số tầng pipeline và giao thức bus.

Cortex-M3 và Cortex-M4 đều được xây dựng dựa trên **kiến trúc ARMv7-M**. Trên cùng một kiến trúc tập lệnh, nhà thiết kế có thể triển khai nhiều vi kiến trúc khác nhau để phù hợp với mục tiêu hiệu năng và phần cứng.

Các thông tin chi tiết của ARMv7-M được mô tả trong tài liệu **ARMv7-M Architecture Reference Manual**, bao gồm:

- Tập lệnh
- Mô hình ngoại lệ
- Mô hình bộ nhớ
- Kiến trúc debug

Về lý thuyết, lập trình viên có thể phát triển phần mềm mà không cần hiểu sâu về vi kiến trúc. Tuy nhiên, trong một số trường hợp như **tối ưu hiệu năng chương trình** hoặc **tối ưu trình biên dịch**, việc nắm được một số chi tiết vi kiến trúc vẫn rất hữu ích.
### 3.1.3 Instruction set
### 3.1.4 Block diagram
### 3.1.5 Memory system
### 3.1.6 Interrupt and exception support

## 3.2 Các đặc điểm của bộ xử lý Cortex®-M3 và Cortex-M4

### 3.2.1 Performance
### 3.2.2 Code density
### 3.2.3 Low power
### 3.2.4 Memory system
### 3.2.5 Memory protection unit
### 3.2.6 Interrupt handling
### 3.2.7 OS support and system level features
### 3.2.8 Cortex®-M4 specific features
### 3.2.9 Ease of use
### 3.2.10 Debug support
### 3.2.11 Scalability
### 3.2.12 Compatibility
