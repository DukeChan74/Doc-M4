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



![Memorymap](https://raw.githubusercontent.com/DukeChan74/Doc-M4/main/picture/005/Memorymap_4gb.png)

![Memorymaptable](https://raw.githubusercontent.com/DukeChan74/Doc-M4/main/picture/005/Table6.1.png)

