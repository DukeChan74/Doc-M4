# Chapter 6: Memory map

## 6.1 Overview

Các Cortex‑M processors có khả năng 32‑bit memory addressing, do đó có 4GB memory space. Không gian bộ nhớ này là unified, nghĩa là instructions và data cùng chia sẻ một không gian địa chỉ. Vùng nhớ 4GB này được chia thành nhiều regions về mặt kiến trúc, sẽ được giải thích trong Section 6.2 memory maps.

Ngoài ra, hệ thống bộ nhớ của Cortex‑M3 và Cortex‑M4 processors hỗ trợ một số tính năng:

- Multiple bus interfaces cho phép truy cập đồng thời instructions và data (Harvard bus architecture).

- Thiết kế bus dựa trên AMBA (Advanced Microcontroller Bus Architecture), một chuẩn bus trên chip phổ biến:

    - AHB (AMBA High‑performance Bus) Lite protocol cho các thao tác pipeline trong bộ nhớ và system bus.

    - APB (Advanced Peripheral Bus) protocol cho giao tiếp với các thành phần debug.

- Hỗ trợ cả little endian và big endian memory systems.

- Hỗ trợ unaligned data transfers.

- Hỗ trợ exclusive accesses (cho các thao tác semaphore trong hệ thống có embedded OS hoặc RTOS).

- Bit addressable memory spaces (bit‑band).

- Memory attributes và access permissions cho các vùng nhớ khác nhau.

- Một Memory Protection Unit (MPU) tùy chọn. Các cấu hình memory attributes và access permissions có thể được lập trình tại runtime nếu MPU khả dụng.

Processor và architecture cho phép cấu hình bộ nhớ rất linh hoạt, vì vậy bạn có thể tìm thấy các Cortex‑M3 và Cortex‑M4 based microcontrollers với nhiều kích thước bộ nhớ và memory maps khác nhau. Ngoài ra, một số sản phẩm Cortex‑M microcontroller còn có các tính năng hệ thống bộ nhớ đặc thù, chẳng hạn như memory address remapping/alias.

## 6.2 Memory map

### Memory Map trong Cortex‑M

Trong 4GB addressable memory space, một phần được cấp phát cho các internal peripherals bên trong processor như NVIC và các thành phần debug. Các địa chỉ bộ nhớ của những thành phần nội bộ này là fixed. Ngoài ra, không gian bộ nhớ được chia thành nhiều memory regions về mặt kiến trúc như minh họa trong Figure 6.1.  

### Ưu điểm của cách sắp xếp
- Cho phép thiết kế processor hỗ trợ nhiều loại memories và devices ngay từ đầu.  
- Bố cục được tối ưu để đạt hiệu năng cao hơn.  

Mặc dù pre‑defined memory map là cố định, kiến trúc vẫn có tính linh hoạt cao để các silicon designers có thể thiết kế sản phẩm với các loại memories và peripherals khác nhau nhằm tạo sự khác biệt cho sản phẩm.

---

### Memory Region Definitions
Các memory region definitions được hiển thị ở phía bên trái của Figure 6.1. Mô tả chi tiết của các vùng nhớ này được liệt kê trong Table 6.1.

- Có thể lưu trữ và thực thi program code trong các vùng SRAM và RAM, nhưng thiết kế processor không được tối ưu cho hoạt động này và cần thêm một extra clock cycle cho mỗi lần instruction fetch.  
- Do đó, hiệu năng sẽ chậm hơn một chút khi thực thi program code qua system bus.  
- Việc thực thi chương trình từ các vùng Peripherals, Devices, và System memory là not allowed.  

---

### Built‑in Components
Figure 6.1 cho thấy có một số built‑in components trong memory map. Chúng được mô tả trong Table 6.2.  

Không gian bộ nhớ dành cho NVIC, MPU, SCB, và nhiều system peripherals khác được gọi là System Control Space (SCS). Thông tin chi tiết về các thành phần này sẽ được trình bày trong các chương khác.

![Memorymap](https://raw.githubusercontent.com/DukeChan74/Doc-M4/main/picture/005/Memorymap_4gb.png)

![Memorymaptable](https://raw.githubusercontent.com/DukeChan74/Doc-M4/main/picture/005/Table6.1.png)

