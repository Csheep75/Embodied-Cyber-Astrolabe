# 操作与验证说明（统一固件 · 双板一体）

## 1. 编译与烧录（只做一次）

```bash
cd hareware
idf.py set-target esp32s3
idf.py build
```

**同一份** `build/hareware.bin` 分别烧到 WROOM 与 EYE：

```bash
idf.py -p /dev/ttyUSB_WROOM flash
idf.py -p /dev/ttyUSB_EYE flash
```

- Flash：**8MB**（`sdkconfig.defaults`）  
- 分区：**Single factory app (large)**  
- **不要**再使用 `cp sdkconfig.defaults.wroom/eye`（已删除）

## 2. 同时启动

1. WROOM、EYE **同时上电**（或先后间隔数秒内）  
2. 各接串口或只监视其中一块  
3. 期望日志：

**WROOM (oracle)**

```
main: Mao.exe unified firmware
board_role: role from strap GPIO48: oracle
bringup: Oracle peripherals
pca9685: init ok ...
espnow: init ok (broadcast ch1)
main: running as oracle
```

**EYE (cat)**

```
board_role: role from strap GPIO48: cat
bringup: Cat peripherals
cat_sm: init
espnow: init ok (broadcast ch1)
main: running as cat
```

## 3. 运行时切换演示（无需重新编译）

在 monitor 里输入：

```
mode pet
mode bristle
mode tail
mode spin
mode idle
role
```

另一块板应打印 `espnow: peer demo mode ...` 及对应 `cat_sm` / `oracle_sm` 日志。

## 4. 硬件验证

| 项目 | 操作 | 合格 |
|------|------|------|
| 角色 | 上电看 `role from strap` | WROOM=oracle，EYE=cat |
| ESP-NOW | 一块发 `mode pet` | 另一块有 espnow 日志 |
| PCA9685 | WROOM 上电 | `pca9685: init ok` |
| 霍尔 | 磁铁靠近 GPIO4 | 后续 API 低电平触发 |
| 步进 | WROOM 上电 | `stepper: gpio init ok` |

## 5. menuconfig（可选）

`Hareware → Board role`：

- **Auto detect**（默认，量产用）  
- Force Oracle / Force Cat：仅调试

## 6. 修改接线后

1. 改 `components/shared/hardware_config.h`  
2. 改 `docs/tables/01_wiring_*.csv`  
3. `idf.py build flash`（两块板各烧一次）
