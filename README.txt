TESMIOINDUSTRY — TESMIO / Republic Mod Loader 安装说明
====================================================

运行包结构
README.txt、previewimage.png 放在根目录；插件 DLL、INI 和 RML 元数据放在 plugins 目录。
本包面向 WRSR 1.1.1.9（64 位）。DLL 使用 TESMIO API 4；RML 使用其 TESMIO 兼容宿主加载。

TESMIO 安装
1. 完全退出游戏，从本包 plugins 目录复制 TESMIOINDUSTRY.dll 和 TESMIOINDUSTRY.ini 到：
   <游戏目录>\tesmioloader\build\plugins\（tesmioloader.dll 旁的 plugins 目录）。
2. 启用 TESMIO 插件扫描；若 [plugins] 显式关闭了 TESMIOINDUSTRY，将其设为 1。
3. 使用 tesmiolauncher.exe 启动。RML 的 .rml.json 元数据无需复制给 TESMIO。

Republic Mod Loader（RML）安装
1. 订阅并下载对应创意工坊项目后，使用支持 TESMIO API 4 的 RML 启动器。
2. 刷新列表，在 Plugins 中启用 TESMIOINDUSTRY；工坊文件应位于 <项目编号>\plugins\。
3. 手动安装时，将本包 plugins 内的 DLL、INI、.rml.json 复制到 RML 的 rml\plugins\。
4. INI 与实际加载的 DLL 放在同一目录。若已有手动安装副本，先备份个人设置再统一安装来源。

配置与发布
编辑实际加载目录内的 INI；保存为 UTF-8 无 BOM，并完整重启游戏。
同一个游戏进程选择一个 Loader 启动。可选的 Reputation 联动不构成强制依赖。
上传目录应包含 plugins、README.txt、previewimage.png 及该项目原有的 workshopconfig.ini。
保留各项目的 ITEM_ID、OWNER_ID 和可见性，使用 SCRIPT 项目类型；不要上传传输 ZIP。
本次调整验证了打包结构和接口；调整参数后的游戏效果及存档兼容性仍需实际运行验证。

English installation
====================
Target: WRSR 1.1.1.9 x64; TESMIO API 4 or RML with the TESMIO API 4 compatibility host.
TESMIO: copy TESMIOINDUSTRY.dll and TESMIOINDUSTRY.ini from this package's plugins folder into
<game>\tesmioloader\build\plugins, enable the plugin, and launch with tesmiolauncher.exe.
RML Workshop: subscribe/download the item, refresh the inventory and enable TESMIOINDUSTRY.
RML manual: copy DLL, INI and .rml.json from plugins into RML's rml\plugins folder.
Keep the INI beside the DLL that is actually loaded. Edit settings, then fully restart.
Use one loader per game process. Reputation integration is optional, not a required dependency.
Publish the plugins folder with root README/preview and the item's original workshopconfig.ini;
preserve item/owner IDs and visibility, use SCRIPT type, and do not upload the transfer ZIP.
Package/interface checks do not establish gameplay behavior or save compatibility.

功能与参数 / Features and settings
====================================================
TESMIOINDUSTRY 0.1.0 — 工业生产调节 / Industrial Production Controls

中文
需要 TESMIO API 4；本地目标为 WRSR 1.1.1.9、TESMIO b0.3.6。
将 TESMIOINDUSTRY.dll 和 TESMIOINDUSTRY.ini 复制到 TESMIO 的 build\plugins，
通过 TESMIO 启动游戏。修改 INI 后重新启动游戏。
如果 tesmioloader.ini 的 [plugins] 已写 TESMIOINDUSTRY=0，请改为 1。
独立使用不需要 resources、needs 或其他功能插件。两个新 MOD 可以一起使用。

所有倍率默认 1.0，范围 0.05—20；enabled=0 关闭本 MOD。
[global] 为全局，分类章节为分类， [building.文件名] 为单建筑覆盖。
三层倍率相乘；文件名不含 .ini，如 [building.steel_mill_v2]。
input_multiplier：原料投入倍率；output_multiplier：产品产出倍率。
efficiency_multiplier：单位时间处理量；utility_multiplier：按秒消耗的公用资源倍率。
最终投入 = 原投入 × 效率 × 投入倍率；最终产出 = 原产出 × 效率 × 产出倍率。
按秒消耗 = 原按秒消耗 × 效率 × 公用资源倍率。
每个建筑的实际产量仍受工人数、生产率、矿源、供电和库存限制。
效率不改变职工需求，也不会自动提高物流能力或储存容量。

分类 / Categories
extraction：采掘 / Extraction
ore_processing：选矿与骨料加工 / Ore and aggregate processing
construction_materials：砖、水泥、混凝土、沥青、预制板 / Construction materials
metallurgy：钢、氧化铝、铝 / Metallurgy
chemicals：化工、炼油、塑料、液肥、炸药 / Chemicals and refining
nuclear：铀加工与核燃料 / Nuclear processing
mechanical：机械组件 / Mechanical components
electronics：电子组件和电子产品 / Electronic components and electronics
wood：伐木和木板 / Timber and boards
food：食品、酒、肉、畜牧 / Food, alcohol, meat and livestock
textiles：布料和服装 / Fabric and clothing
energy：发电和供热 / Electricity and heat
water：水源、水处理、污水处理 / Water and sewage
recycling：含废料投入的回收配方 / Waste-input recycling recipes
other_factory：其他可识别工厂 / Other recognized factories

例：在 [metallurgy] 设置效率 1.2、投入 0.9、产出 1.1，
则同样条件下投入为原来的 1.08 倍，产出为 1.32 倍；单位产品耗料约为原来的 81.8%。
仅提高效率会同步增加投入和产出，不会改善单位产品耗料。
include_workshop=1 才处理可识别的创意工坊建筑，默认关闭。
按配方分类；使用废料的化肥厂属于 recycling。

范围：不调整农田成熟/收获、不调整车辆装配线的单车配方或装配工时。
vehicles=1 是特殊标记，即使在核燃料工厂中也保持原值。
没有 $PRODUCTION 的垃圾分拣、原生特殊机制和建筑生活耗电不在此倍率范围内。
既有 VFS 数据先作为输入；本 MOD 只改变读取时的数值，不覆盖原始文件。

验证：已通过编译、实际 DLL 的模拟宿主测试、所有原版生产 INI 的倍率检查，
以及仅 TESMIO 和当前功能插件组合的启动检查。
地图内持续生产、研究解锁和存档重载仍需测试；0.1.0 为实验版本。

English
Requires TESMIO API 4. Local target: WRSR 1.1.1.9 with TESMIO b0.3.6.
Copy the DLL and INI into TESMIO's build\plugins and launch through TESMIO.
Restart after editing settings. Enable TESMIOINDUSTRY in [plugins] if explicitly disabled.
No other feature plugin is required; compatible import handlers are chained.
All factors default to 1.0. Range: 0.05–20. Set enabled=0 to disable.
Global, category and [building.filename] factors multiply; omit .ini from filename.
Input rate = original input × efficiency × input_multiplier.
Output rate = original output × efficiency × output_multiplier.
Per-second utility rate = original utility × efficiency × utility_multiplier.
Worker counts, storage, vehicle logistics and native operating constraints still apply.
Example: efficiency 1.2, input 0.9, output 1.1 gives 1.08× input and 1.32× output.
Use include_workshop=1 to opt into recognized Workshop recipes.
Fields, farm harvests, vehicle assembly recipes/workdays, vehicles markers,
non-recipe waste sorting and living-worker utility formulas are outside scope.
VFS inputs are preserved; transformations are temporary and do not edit game/save files.
Compiled DLL tests and startup checks passed. In-world production and save reload
are still unverified. Version 0.1.0 is experimental.

GitHub: https://github.com/HONGxuanzhao/TESMIOINDUSTRY
