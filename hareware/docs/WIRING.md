# 双板一体 — 实物接线与上电流程

**一份固件、两块板同时上电**，通过 ESP-NOW 同步演示模式，**无需 `cp sdkconfig`、无需为切换演示重新编译**。

---

## 1. 系统架构

```text
  5V 电源 (共地)                    5V / USB
       │                                │
       ▼                                ▼
┌──────────────────┐    ESP-NOW 信道1    ┌──────────────────┐
│ ESP32-S3-WROOM   │◄──────────────────►│ ESP32-S3-EYE     │
│ GPIO48 ──► GND   │   同步 demo 模式    │ GPIO48 悬空      │
│ 角色: oracle     │                    │ 角色: cat        │
│ PCA9685/步进/霍尔 │                    │ ToF/触摸/屏/摄像头 │
└──────────────────┘                    └──────────────────┘
```

| 项目 | 说明 |
|------|------|
| 固件 | **同一份** `hareware.bin` 分别烧录到两块板 |
| 角色识别 | ① STRAP 脚 ② I2C 探测 PCA9685 ③ 默认 cat |
| 演示切换 | 任意一块板串口输入 `mode pet` 等，**ESP-NOW 广播**到另一块 |

---

## 2. 角色识别线（必接）

| 板子 | GPIO 48 (STRAP) | 识别结果 |
|------|-----------------|----------|
| **WROOM 载板** | **接 GND** | `oracle`（转盘/舵机） |
| **EYE 本体** | **悬空**（固件内部上拉） | `cat`（喵.exe） |

```text
WROOM:  GPIO48 ──── GND
EYE:    GPIO48 ──── (不接线)
```

---

## 3. WROOM 载板接线（oracle）

### 供电

| 网络 | 接法 |
|------|------|
| SERVO_5V | 适配器 + → PCA9685 V+、舵机红线 |
| STEPPER_5V | 适配器 + → ULN2003 + |
| GND | **星形共地**：ESP、PCA、舵机、步进、霍尔 |
| ESP 3V3 | USB 或 LDO → ESP、PCA VCC、霍尔 VCC |

### 信号

| ESP32-S3 | 外设 |
|----------|------|
| GPIO **8** | PCA9685 SDA |
| GPIO **9** | PCA9685 SCL |
| 3V3 / GND | PCA9685 VCC / GND；OE、A0–A5 接 GND |
| PCA PWM0–7 | MG90S S01–S08 信号（橙） |
| PCA PWM8 | 20kg BIG1 信号 |
| GPIO **14,26,27,33** | ULN2003 IN1–IN4 |
| GPIO **4** | 霍尔 OUT |

---

## 4. EYE 板接线（cat）

| 功能 | 接法 |
|------|------|
| 摄像头 / 屏 | 板载 FPC |
| USB | 供电 + 烧录 + 串口 |
| GPIO **48** | 悬空（角色 cat） |
| ToF / 触摸 / WS2812 | 按 `hardware_config.h` 中 `HW_CAT_*` 填写后接线（当前 NC） |

---

## 5. 上电与展示流程

### 一次性准备

```bash
cd hareware
idf.py set-target esp32s3
idf.py build
# 同一 bin 烧录两块板（换 USB 口各烧一次）
idf.py -p /dev/ttyUSB0 flash
idf.py -p /dev/ttyUSB1 flash
```

### 每次展示

1. **两块板同时上电**（可先 WROOM 再 EYE，间隔 <3s 即可）  
2. 打开 **任一块** 的串口监视器：`idf.py -p PORT monitor`  
3. 确认日志：  
   - WROOM：`role from strap ... oracle`  
   - EYE：`role from strap ... cat`  
   - 两侧：`espnow: init ok`  
4. **切换演示**（无需重编译），在串口输入：

| 命令 | 效果 |
|------|------|
| `mode idle` | 待机 |
| `mode pet` | 摸头撒娇（cat 板日志） |
| `mode bristle` | 炸毛（两侧协同日志） |
| `mode tail` | 摸尾抗议 |
| `mode spin` | 转盘（oracle 板） |
| `role` | 查看本板角色与当前模式 |

命令经 **ESP-NOW 广播**，另一块板同步执行。

### 可选：NVS 强制角色（调试用）

```bash
# 仅开发排查时使用 idf.py menuconfig → Force Oracle / Force Cat
```

---

## 6. 线色建议

| 信号 | 颜色 |
|------|------|
| 5V | 红（粗） |
| GND | 黑 |
| I2C SDA/SCL | 黄/绿 |
| STRAP→GND (WROOM) | 黑或白 |
| 舵机信号 | 橙 |

---

## 7. 检查清单

- [ ] 两块板均已烧录**同一** `hareware.bin`  
- [ ] WROOM 的 GPIO48 已接 GND；EYE 的 GPIO48 未接  
- [ ] 舵机 5V 未从 ESP 3V3 取电  
- [ ] 两板 GND 共地（若电源分开，用粗线短接）  
- [ ] 未使用 ESP32-S3 不存在的 GPIO **22–25**  

详见表格：`docs/tables/01_wiring_wroom.csv`、`01_wiring_eye.csv`。
