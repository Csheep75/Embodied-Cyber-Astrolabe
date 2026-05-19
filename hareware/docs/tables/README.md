# 表格目录

用 Excel / 飞书多维表打开 CSV 即可编辑。版本号、commit 与 `hardware_config_*.{h}` 中的 `HW_CONFIG_VERSION` 保持一致。

- **WROOM**：转盘、PCA9685、步进、霍尔 → `01_wiring_wroom.csv`  
- **EYE**：喵.exe 本体 → `01_wiring_eye.csv`（引脚待标定）  
- **舵机/动作**：`05_servo_map.csv`、`06_motion.csv`（数值后续填写）

操作与烧录验证见 [`../VERIFY.md`](../VERIFY.md)。
