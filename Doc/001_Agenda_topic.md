# 001 - Agenda Topic: Tổng quan về Core trong Vi Điều Khiển

## 1. Tại sao cần hiểu về Core

Trong quá trình phát triển hệ thống nhúng, nhiều người thường tập trung vào việc sử dụng thư viện, cấu hình ngoại vi (GPIO, UART, ADC,...) mà ít quan tâm đến **core (CPU core)** – thành phần thực sự thực thi chương trình.

Tuy nhiên, việc hiểu rõ về core là yếu tố then chốt giúp nâng cao năng lực kỹ thuật, đặc biệt trong các tình huống sau:

---

### 1.1 Hiểu cách chương trình được thực thi

Core là nơi:

- Đọc và thực thi từng lệnh trong chương trình  
- Quản lý thanh ghi (register)  
- Điều khiển luồng chạy (flow control)  

Khi hiểu cách core hoạt động, chúng ta có thể:

- Biết được chương trình đang chạy ở đâu  
- Hiểu vì sao một đoạn code lại cho kết quả như vậy  

---

### 1.2 Hỗ trợ debug hiệu quả

Trong thực tế, các lỗi hệ thống thường không đến từ những phần “dễ thấy” như cấu hình sai GPIO, mà đến từ:

- Truy cập sai địa chỉ bộ nhớ  
- Stack overflow  
- HardFault / BusFault  
- Sai thứ tự thực thi lệnh  

Nếu không hiểu core, việc debug sẽ mang tính “thử sai” (trial-and-error).

Ngược lại, khi hiểu core, chúng ta có thể:

- Đọc và phân tích **register** khi debug  
- Hiểu ý nghĩa của các lỗi exception (HardFault, UsageFault...)  
- Lần theo **stack frame** để tìm vị trí lỗi  
- Xác định chính xác nguyên nhân thay vì đoán  

> Ví dụ: Khi xảy ra HardFault, việc hiểu core giúp đọc được PC, LR và stack để xác định chính xác dòng code gây lỗi.

---

### 1.3 Tối ưu hiệu năng và tài nguyên

Hiểu core giúp:

- Viết code tối ưu hơn (giảm cycle, giảm latency)  
- Tận dụng các tính năng như:  
  - Pipeline  
  - DSP instruction (đối với M4)  
  - FPU  

---

### 1.4 Là nền tảng cho các kiến thức nâng cao

Các chủ đề nâng cao trong embedded đều liên quan trực tiếp đến core:

- Interrupt và NVIC  
- Context switching (RTOS)  
- Memory management  
- Low-level optimization  

Nếu không có nền tảng về core, việc tiếp cận các chủ đề này sẽ khó khăn hơn nhiều.

---

### 1.5 Tóm lại

Hiểu về core không chỉ giúp “biết hệ thống chạy như thế nào”, mà quan trọng hơn:

- Debug nhanh và chính xác hơn  
- Giảm thời gian xử lý lỗi  
- Nâng cao chất lượng code và hệ thống  

> Nói cách khác: Hiểu core là bước chuyển từ “lập trình kiểu sử dụng” sang “lập trình có kiểm soát hệ thống”.

---

## 2. Core là gì?

### 2.1 Định nghĩa

**Core** là đơn vị xử lý trung tâm (CPU) bên trong vi điều khiển, có thể xem như “bộ não” của toàn bộ hệ thống.

Core chịu trách nhiệm:

- Thực thi từng lệnh (instruction) trong chương trình  
- Xử lý dữ liệu (tính toán, logic)  
- Điều khiển luồng thực thi (rẽ nhánh, vòng lặp, gọi hàm)  
- Quản lý thanh ghi (register) và stack  

Nói cách khác, **mọi dòng code chúng ta viết cuối cùng đều được thực thi bởi core**.

---

### 2.2 Core trong thực tế (ví dụ STM32)

Trong các vi điều khiển hiện đại như STM32:

- Nhà sản xuất (ST) **không tự thiết kế core**  
- Họ sử dụng core từ ARM (ví dụ: Cortex-M0, M3, M4, M7)

👉 Ví dụ:

- STM32F4 sử dụng **ARM Cortex-M4 core**  
- Core chạy với xung nhịp lên tới ~168MHz  
- Có hỗ trợ DSP và FPU giúp xử lý tín hiệu nhanh hơn  

➡️ Điều này có nghĩa:

> STM32 = Core (ARM Cortex-M4) + Memory + Peripheral

---

### 2.3 Core nằm trong kiến trúc MCU như thế nào?

Trong một vi điều khiển (MCU), core chỉ là **một phần trong toàn bộ hệ thống**, bao gồm:

- **Core (CPU)**: xử lý trung tâm  
- **Flash**: lưu chương trình  
- **RAM**: lưu dữ liệu runtime  
- **Peripheral**: GPIO, UART, ADC, Timer...  
- **Bus system**: kết nối các thành phần  

Core sẽ:

- Lấy lệnh từ Flash  
- Xử lý dữ liệu trong RAM  
- Điều khiển peripheral thông qua thanh ghi (register)  

👉 Toàn bộ quá trình này diễn ra thông qua **bus nội bộ (AHB, APB,...)**

---

### 2.4 Phân biệt các thành phần

| Thành phần | Vai trò |
|-----------|--------|
| Core      | Xử lý trung tâm, thực thi lệnh |
| Memory    | Lưu trữ chương trình và dữ liệu |
| Peripheral| Giao tiếp với bên ngoài (GPIO, UART, ADC...) |

📌 **Điểm quan trọng:**

- Core **không trực tiếp “chạm” vào phần cứng bên ngoài**

- Mọi thứ đều thông qua:
  - Thanh ghi (register)
  - Memory-mapped I/O

---

### 2.5 Góc nhìn trực quan

Có thể hình dung:

- Core = **CPU của máy tính**  
- MCU = **một hệ thống hoàn chỉnh thu nhỏ trên một chip**  

Hình minh họa:

![STM32-M4](https://admin.devstack.it.com/uploads/STM_32_M4_139aef8f00.png)

---

### 2.6 Tóm lại

- Core là thành phần quan trọng nhất của vi điều khiển  
- Các dòng MCU có thể giống peripheral nhưng khác core → hiệu năng và cách lập trình khác nhau  

Ví dụ:

- STM32F1 → Cortex-M3  
- STM32F4 → Cortex-M4  
- STM32F7 → Cortex-M7  

👉 Vì vậy:

> Hiểu core chính là hiểu “cách hệ thống thực sự hoạt động bên trong”.

---

## 3. Tổng quan về các dòng ARM Cortex-M

ARM Cortex-M là họ core phổ biến trong vi điều khiển hiện đại, bao gồm:

- Cortex-M0 / M0+  
- Cortex-M3  
- Cortex-M4  
- Cortex-M7  

---

### 3.1 So sánh nhanh

| Core | Đặc điểm | Ứng dụng |
|------|---------|---------|
| M0/M0+ | Đơn giản, tiết kiệm năng lượng | Thiết bị nhỏ, IoT |
| M3     | Cân bằng hiệu năng | Ứng dụng phổ thông |
| M4     | Có DSP, FPU | Xử lý tín hiệu, điều khiển |
| M7     | Hiệu năng cao | Ứng dụng phức tạp |

---

## 4. Tại sao Cortex-M4 phổ biến?

### 4.1 Đặc điểm nổi bật

Cortex-M4 được sử dụng rộng rãi nhờ:

- Hỗ trợ **DSP instructions**  
- Tích hợp **FPU (Floating Point Unit)**  
- Hiệu năng tốt so với chi phí  

---

### 4.2 Ứng dụng thực tế

- IoT (Internet of Things)  
- Điều khiển động cơ (Motor Control)  
- Xử lý âm thanh (Audio Processing)  
- Thiết bị công nghiệp  

---

### 4.3 Các dòng vi điều khiển sử dụng M4

- STM32F4 (STMicroelectronics)  
- NXP Kinetis  
- TI Tiva C Series  

---

## 5. Tổng kết

Core là nền tảng của mọi hệ thống nhúng. Việc hiểu rõ core giúp:

- Nắm được cách chương trình thực thi  
- Debug hiệu quả hơn  
- Tối ưu hệ thống tốt hơn  

Và quan trọng nhất:

> Nó giúp bạn chuyển từ “viết code để chạy” sang “viết code để kiểm soát hệ thống”.
