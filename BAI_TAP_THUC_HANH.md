# BÀI TẬP THỰC HÀNH STM32 REGISTER - TỪ DỄ ĐẾN KHÓ

> Dựa trên code hiện có: GPIO, RCC, EXTI, AFIO
> Hardware: STM32F103C8T6 (Blue Pill)

---

## 🟢 LEVEL 1: BASIC GPIO (1-2 tuần)

### **BÀI 1.1: LED Blink đơn giản**
**Mục tiêu:** Làm quen GPIO Output
**Hardware:** 1 LED nối vào PC13 (built-in LED trên Blue Pill)

**Yêu cầu:**
- Bật/tắt LED mỗi 500ms
- Sử dụng hàm `mDelay()` có sẵn
- Không dùng HAL/SPL

**Code cần viết:**
```c
// Trong main.c
RCC_Enable_PortC();
GPIO_Config(GPIOC, GPIO_PIN_13, GPIO_Mode_Output_PP);

while(1) {
    GPIO_Write(GPIOC, GPIO_PIN_13, 1);  // LED ON
    mDelay(500000);
    GPIO_Write(GPIOC, GPIO_PIN_13, 0);  // LED OFF
    mDelay(500000);
}
```

**Thách thức thêm:**
- Thay đổi tần số blink (100ms, 1s, 2s)
- Tính toán giá trị `mDelay()` chính xác với clock 8MHz

---

### **BÀI 1.2: LED Pattern (Running Light)**
**Mục tiêu:** Điều khiển nhiều GPIO
**Hardware:** 4 LED nối vào PC0, PC1, PC2, PC3

**Yêu cầu:**
- LED chạy từ trái sang phải (PC0→PC1→PC2→PC3)
- Mỗi LED sáng 200ms rồi tắt
- Lặp lại liên tục

**Code cần viết:**
```c
// TODO: Tự viết hàm LED_Pattern()
void LED_Pattern() {
    for (uint8_t i = 0; i < 4; i++) {
        GPIO_Write(GPIOC, GPIO_PIN_0 << i, 1);
        mDelay(200000);
        GPIO_Write(GPIOC, GPIO_PIN_0 << i, 0);
    }
}
```

**Thách thức thêm:**
- Pattern ping-pong (trái→phải→trái)
- Pattern knight rider (2 LED chạy từ 2 đầu)

---

### **BÀI 1.3: Button đọc trạng thái (Polling)**
**Mục tiêu:** GPIO Input, đọc nút nhấn
**Hardware:** 1 nút nhấn nối PA0 (pull-down), 1 LED PC13

**Yêu cầu:**
- Nhấn nút → LED sáng
- Thả nút → LED tắt
- Dùng hàm `GPIO_Read()`

**Code mẫu:**
```c
RCC_Enable_PortA();
RCC_Enable_PortC();
GPIO_Config(GPIOA, GPIO_PIN_0, GPIO_Mode_Input_PD);
GPIO_Config(GPIOC, GPIO_PIN_13, GPIO_Mode_Output_PP);

while(1) {
    if (GPIO_Read(GPIOA, GPIO_PIN_0)) {
        GPIO_Write(GPIOC, GPIO_PIN_13, 1);
    } else {
        GPIO_Write(GPIOC, GPIO_PIN_13, 0);
    }
}
```

**Thách thức thêm:**
- Thêm debounce (chống rung phím)
- Nhấn 1 lần toggle (không phải giữ)

---

### **BÀI 1.4: Button Toggle với Debounce**
**Mục tiêu:** Xử lý debounce bằng software
**Hardware:** Giống bài 1.3
                      
**Yêu cầu:**
- Nhấn nút 1 lần → LED toggle (sáng↔tắt)
- Không bị nhiễu (nhấn 1 lần chỉ toggle 1 lần)

**Gợi ý thuật toán:**
```c
uint8_t button_pressed = 0;

while(1) {
    uint8_t current_state = GPIO_Read(GPIOA, GPIO_PIN_0);
    
    if (current_state && !button_pressed) {
        mDelay(20000);  // Debounce delay 20ms
        if (GPIO_Read(GPIOA, GPIO_PIN_0)) {  // Confirm still pressed
            // TODO: Toggle LED
            button_pressed = 1;
        }
    } else if (!current_state) {
        button_pressed = 0;
    }
}
```

**Tự làm:** Hoàn thiện code toggle LED

---

## 🟡 LEVEL 2: EXTERNAL INTERRUPT (2-3 tuần)

### **BÀI 2.1: Button Interrupt cơ bản**
**Mục tiêu:** Dùng EXTI thay vì polling
**Hardware:** Nút PA0, LED PC13

**Yêu cầu:**
- Nhấn nút (rising edge) → Toggle LED
- Sử dụng EXTI0 interrupt
- Xử lý trong ISR

**Code cần sửa trong `EXTI.c`:**
```c
// TODO: Bổ sung vào EXTI0_IRQHandler()
void EXTI0_IRQHandler(void)
{
    if (EXTI->_PR.Bits.bit_0) {
        // TODO: Toggle LED PC13 ở đây
        
        EXTI->_PR.REG |= 1;  // ding flag
    }
}
```

**Lưu ý:**
- Phải clear pending bit trong ISR
- LED toggle logic cần viết tay (dùng XOR với ODR)

**Thách thức thêm:**
- Đếm số lần nhấn và hiển thị qua LED (binary)
- Thêm timeout: nếu không nhấn trong 10s → reset counter

---

### **BÀI 2.2: Debounce trong Interrupt**
**Mục tiêu:** Xử lý debounce với interrupt
**Hardware:** Giống bài 2.1

**Vấn đề:** Interrupt trigger nhiều lần do rung phím

**Giải pháp:**
1. Disable interrupt trong ISR
2. Delay 20-50ms
3. Enable lại interrupt

**Code gợi ý:**
```c
void EXTI0_IRQHandler(void)
{
    if (EXTI->_PR.Bits.bit_0) {
        EXTI->_IMR.Bits.bit_0 = 0;  // Disable EXTI0 temporarily
        
        // TODO: Toggle LED
        
        mDelay(50000);  // Debounce 50ms
        EXTI->_PR.REG |= 1;
        EXTI->_IMR.Bits.bit_0 = 1;  // Re-enable
    }
}
```

**Thách thức thêm:**
- Dùng timer thay vì delay blocking
- Phát hiện long press (giữ > 2 giây)

---

### **BÀI 2.3: Multi-button Interrupt (EXTI1, EXTI2)**
**Mục tiêu:** Xử lý nhiều interrupt
**Hardware:** 
- Button 1: PA0 (EXTI0) → LED PC13
- Button 2: PA1 (EXTI1) → LED PC14
- Button 3: PA2 (EXTI2) → LED PC15

**Yêu cầu:**
- Mỗi nút điều khiển 1 LED riêng
- Viết thêm `EXTI1_Init()`, `EXTI2_Init()` trong `EXTI.c`
- Viết thêm `EXTI1_IRQHandler()`, `EXTI2_IRQHandler()`

**Gợi ý:**
- Tham khảo code `EXTI0_Init()` hiện có
- Thay đổi bit position tương ứng
- Check NVIC interrupt number cho EXTI1 (IRQ 7), EXTI2 (IRQ 8)

---

### **BÀI 2.4: LED Pattern với Interrupt**
**Mục tiêu:** Kết hợp interrupt + state machine
**Hardware:** 1 nút PA0, 4 LED PC0-PC3

**Yêu cầu:**
- Nhấn nút → đổi pattern:
  - Mode 1: LED chạy từ trái sang phải
  - Mode 2: LED chạy từ phải sang trái
  - Mode 3: LED nhấp nháy đồng thời
  - Mode 4: LED knight rider

**Thuật toán:**
```c
uint8_t led_mode = 0;

void EXTI0_IRQHandler(void) {
    if (EXTI->_PR.Bits.bit_0) {
        led_mode = (led_mode + 1) % 4;  // Cycle through 4 modes
        EXTI->_PR.REG |= 1;
    }
}

void main() {
    // Init...
    while(1) {
        switch(led_mode) {
            case 0: LED_Pattern_LeftToRight(); break;
            case 1: LED_Pattern_RightToLeft(); break;
            case 2: LED_Pattern_Blink(); break;
            case 3: LED_Pattern_KnightRider(); break;
        }
    }
}
```

**Tự làm:** Viết 4 hàm pattern

---

## 🟠 LEVEL 3: TIMER & ADVANCED (3-4 tuần)

### **BÀI 3.1: SysTick Timer - Delay chính xác**
**Mục tiêu:** Thay thế `mDelay()` bằng SysTick
**Lý do:** `mDelay()` không chính xác, phụ thuộc compiler optimization

**Yêu cầu:**
- Viết driver SysTick
- Tạo hàm `delay_ms(uint32_t ms)` chính xác
- LED blink chính xác 500ms

**File cần tạo:** `Driver/SysTick.h`, `Driver/SysTick.c`

**Gợi ý cấu trúc:**
```c
// SysTick.h
typedef struct {
    uint32_t CTRL;
    uint32_t LOAD;
    uint32_t VAL;
    uint32_t CALIB;
} SysTick_Type;

#define SysTick ((volatile SysTick_Type*) 0xE000E010UL)

void SysTick_Init();
void delay_ms(uint32_t ms);
```

**Tự nghiên cứu:**
- SysTick register (ARM Cortex-M3 manual)
- Clock source: 72MHz hoặc 72MHz/8

---

### **BÀI 3.2: Timer 2 - PWM LED Breathing**
**Mục tiêo:** Tạo PWM bằng Timer
**Hardware:** LED PC13 (hoặc PA0 - TIM2_CH1)

**Yêu cầu:**
- LED fade in/out mượt (breathing effect)
- Dùng Timer 2 PWM mode
- Điều chỉnh duty cycle từ 0-100%

**File cần tạo:** `Driver/TIM.h`, `Driver/TIM.c`

**Gợi ý:**
```c
void TIM2_PWM_Init() {
    // TODO: 
    // 1. Enable TIM2 clock (RCC)
    // 2. Configure prescaler & ARR
    // 3. Set CCR1 for duty cycle
    // 4. Enable PWM mode
}

void LED_Breathing() {
    for (uint16_t duty = 0; duty <= 100; duty++) {
        TIM2->CCR1 = duty;
        delay_ms(10);
    }
    for (uint16_t duty = 100; duty > 0; duty--) {
        TIM2->CCR1 = duty;
        delay_ms(10);
    }
}
```

---

### **BÀI 3.3: Reaction Time Game**
**Mục tiêu:** Kết hợp interrupt + timer
**Hardware:** 1 nút PA0, 1 LED PC13

**Gameplay:**
1. LED tắt, chờ random 1-5 giây
2. LED sáng
3. Người chơi nhấn nút nhanh nhất
4. Đo thời gian phản ứng (ms)
5. Hiển thị kết quả bằng LED blink (số lần = số trăm ms)

**Yêu cầu kỹ thuật:**
- Dùng SysTick đếm thời gian
- Random delay bằng cách lấy số lẻ từ timer counter
- Phát hiện early press (nhấn trước khi LED sáng) → invalid

---

### **BÀI 3.4: Button Combo Detection**
**Mục tiêu:** Phát hiện chuỗi nhấn phím
**Hardware:** 2 nút PA0, PA1, LED PC13

**Yêu cầu:**
- Phát hiện combo: UP-UP-DOWN-UP (trong 3 giây)
- Nếu đúng → LED sáng 5 giây
- Nếu sai hoặc timeout → reset

**Kỹ thuật:**
- Dùng array lưu trạng thái nhấn
- Dùng SysTick đo timeout
- State machine để verify sequence

---

## 🔴 LEVEL 4: REAL PROJECT (1-2 tháng)

### **PROJECT 1: Smart Lock với Keypad 4x4**
**Mục tiêu:** Tích hợp toàn bộ kiến thức
**Hardware:**
- Keypad 4x4 matrix
- LED RGB (hoặc 3 LED riêng)
- Buzzer (optional)

**Tính năng:**
- Nhập mã PIN 4 số
- LED xanh + unlock nếu đúng
- LED đỏ + buzzer nếu sai
- Sai 3 lần → khóa 30 giây
- Timeout 10s không nhập → reset

**Kỹ thuật:**
- GPIO scanning (row output, column input)
- Debounce phức tạp
- State machine
- Timer countdown

---

### **PROJECT 2: Traffic Light Controller**
**Mục tiêu:** Mô phỏng đèn giao thông thực tế
**Hardware:**
- 6 LED (2 hướng, mỗi hướng 3 đèn: đỏ, vàng, xanh)
- 1 nút (chế độ pedestrian crossing)

**Tính năng:**
- Đèn tự động chuyển theo chu kỳ
- Nhấn nút → chuyển sang chế độ người đi bộ
- LED countdown (nếu có 7-segment display)

---

### **PROJECT 3: Simple RTOS (Round-robin Scheduler)**
**Mục tiêo:** Tạo hệ thống đa tác vụ đơn giản
**Yêu cầu:**
- 3 task chạy đồng thời:
  - Task 1: LED 1 blink 1Hz
  - Task 2: LED 2 blink 2Hz
  - Task 3: Đọc nút và toggle LED 3
- Dùng SysTick interrupt để switch task

**Kỹ thuật:**
- Context switching (đơn giản, không cần stack)
- Task struct với function pointer
- Round-robin scheduling

---

## 📚 TÀI NGUYÊN HỌC TẬP

### Documents cần đọc:
1. **STM32F103 Reference Manual (RM0008)** - Chương:
   - GPIO (Chapter 9)
   - RCC (Chapter 7)
   - EXTI (Chapter 10)
   - NVIC (Chapter 12 - Cortex-M3 manual)
   - Timer (Chapter 15)

2. **STM32F103 Datasheet** - Pinout, electrical specs

3. **ARM Cortex-M3 Programming Manual** - SysTick, NVIC

### Tips học hiệu quả:
- ✅ Code từ blank file, không copy-paste
- ✅ Viết comment giải thích **TẠI SAO**, không phải **CÁI GÌ**
- ✅ Làm từng bài theo thứ tự, không nhảy cóc
- ✅ Review lại code sau 1 tuần
- ✅ Làm project thực tế có ý nghĩa
- ❌ Không dùng HAL/SPL trong giai đoạn này

---

**MÀY BẮT ĐẦU TỪ BÀI NÀO?**
Gợi ý: Bắt đầu từ **Bài 1.1** nếu mày còn lạ GPIO, hoặc **Bài 2.1** vì mày đã có code EXTI rồi.
