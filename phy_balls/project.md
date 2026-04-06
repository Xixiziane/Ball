# 物理小球模拟项目

## 项目概述

这是一个基于 SFML 的 2D 物理小球模拟与交互应用。用户可以通过键盘 (WASD) 控制一个可玩小球，与场景中其他自由运动的小球互动，系统模拟了重力、碰撞、边界反弹等物理效果。

## 项目结构

```
phy_balls/
├── CMakeLists.txt              # CMake 编译配置
├── main.cpp                    # 主程序入口
├── project.md                  # 项目文档（本文件）
├── src/
│   ├── cpp/                    # 源文件实现
│   │   ├── Ball.cpp           # 小球属性实现
│   │   ├── Ball_Player.cpp    # 玩家控制实现
│   │   ├── Physics.cpp        # 物理引擎实现
│   │   └── Windows.cpp        # 渲染与主循环实现
│   └── hpp/                    # 头文件声明
│       ├── Ball.hpp           # 小球类定义
│       ├── Ball_Player.hpp    # 玩家类定义
│       ├── Physics.hpp        # 物理引擎定义
│       └── Windows.hpp        # 窗口类定义
└── build/                      # CMake 编译输出目录
    └── ball                    # 可执行程序
```

## 核心类说明

### 1. **Ball 类** (`src/hpp/Ball.hpp` / `src/cpp/Ball.cpp`)

表示场景中的物理小球。

**成员**:
- `sf::CircleShape *ball` - SFML 圆形图形对象（指针）
- `sf::Vector2f speed` - 小球速度向量
- `float m` - 小球质量

**接口**:
- `Ball(const sf::CircleShape&, const sf::Vector2f&, const float&)` - 构造函数
- `~Ball()` - 析构函数
- `Ball(const Ball&)` - 拷贝构造
- `sf::Vector2f& get_speed()` - 获取/修改速度
- `sf::CircleShape* get_ball()` - 获取形状指针
- `float get_mass() const` - 获取质量

### 2. **Ball_Play 类** (`src/hpp/Ball_Player.hpp` / `src/cpp/Ball_Player.cpp`)

玩家可控的小球，继承自 Ball 并添加输入响应。

**成员**:
- `Ball ball_play` - 被控制的小球对象

**接口**:
- `Ball_Play(const Ball&)` - 构造函数
- `Ball& get_ball()` - 获取内部小球引用
- `void controler(const float dt)` - 逐帧处理用户输入

**控制参数**:
- 加速度 (accel) = 1200.0f
- 最大速度 (maxSpeed) = 280.0f  
- 移动时阻尼 (dragWhenMove) = 7.0f
- 空闲时阻尼 (dragWhenIdle) = 11.0f

**操作方式**:
- `W` - 向上移动
- `S` - 向下移动
- `A` - 向左移动
- `D` - 向右移动

### 3. **Physics 类** (`src/hpp/Physics.hpp` / `src/cpp/Physics.cpp`)

全局物理引擎，处理碰撞检测与响应、边界约束。

**静态方法**:
- `void check_boundary(Ball&, width, height)` - 检查并处理球与边界的碰撞
- `void collision_handing(Ball&, Ball&)` - 处理球与球之间的碰撞

**实现细节**:
- 使用圆心距离判断碰撞
- 边界碰撞时速度反向，位置纠正
- 球碰撞使用动量守恒与能量传递算法（支持不同质量）

### 4. **Windows 类** (`src/hpp/Windows.hpp` / `src/cpp/Windows.cpp`)

窗口管理、渲染与主物理循环。

**成员**:
- `sf::RenderWindow *w` - SFML 窗口指针
- `std::vector<Ball> balls` - 场景中所有非玩家小球
- `Ball_Play player` - 玩家可控小球
- `std::vector<sf::Vector2f> prev_ball_positions` - 上一物理帧球的位置（用于渲染插值）
- `sf::Vector2f prev_player_position` - 玩家球上一物理帧位置

**接口**:
- `Windows(mode, title, balls, player)` - 构造函数
- `~Windows()` - 析构函数
- `void run(float dt)` - 单帧逻辑更新（包含固定步长处理）
- `void Draw()` - 渲染所有小球（使用插值位置）
- `void clear(Color)` - 清空窗口
- `void display()` - 提交渲染
- `sf::RenderWindow* get_windows()` - 获取窗口指针

**私有方法**:
- `void capture_previous_positions()` - 保存每个球的当前位置（用于插值,还未实现）
- `void fixed_update(float dt)` - 执行一步固定时长的物理更新

## 核心功能

### 1. 玩家控制

使用**加速度 + 阻尼 + 最大速度**的三层模型替代硬直设速：
- 按键产生的是**加速度**，而非直接速度改变
- 移动与空闲阶段使用不同的阻尼值，提升操作反馈感
- 最大速度上限防止速度累积过高
- 支持斜向输入归一化，保证各方向移动一致

### 2. 物理模拟

- **碰撞检测**：圆形距离判定
- **碰撞响应**：
  - 位置纠正（防止穿透）
  - 速度投影到法向量和切向的分量处理
  - 支持不同质量的动量守恒计算
- **边界约束**：位置夹乘 + 速度反向

### 3. 固定时间步长 + 渲染插值（还在写）

为保证跨不同帧率的操作手感一致：
- **固定物理步长** (1/120s) - 物理严格按固定频率更新
- **累积器** - 收集实际帧时间，按需执行多次（或零次）物理步
- **渲染插值** - 根据累积器余量对球的位置做线性插值（`lerp`）
  - 使物理离散更新不会导致视觉颤抖或"跳跃"
  - 最终画面显示的位置是上一物理帧与本物理帧的中间态

### 4. 碰撞系统

每帧按以下顺序处理：
1. 玩家输入与加速度
2. 球的位置更新（基于速度）
3. **球-球碰撞**（O(n²) 检查）
4. **球-玩家碰撞**
5. **边界碰撞**（玩家和所有球）

## 编译与运行

### 依赖

- C++11 或更高版本
- SFML（Simple and Fast Multimedia Library）- graphics 模块

### 编译

```bash
cd /home/zian/plyerbird/phy_balls
cmake -B build
cmake --build build
```

### 运行

```bash
./build/ball
```

窗口大小：800x600 像素  
目标帧率：60 FPS  
物理更新频率：120 Hz（内部固定）

## 场景初始化

主程序创建 3 个小球，具体配置见 [main.cpp](main.cpp)：

| 球 | 颜色 | 半径 | 初始位置 | 初始速度 | 质量 | 可控 |
|----|------|------|---------|---------|------|------|
| b1 | 蓝色 | 30   | (400,300) | (20,-30) | 10 | ✗ |
| b2 | 绿色 | 40   | (400,300) | (-30,-40) | 20 | ✗ |
| b3（玩家） | 青色 | 35   | (200,300) | (0,0) | 40 | ✓ |

## game feel 优化说明

本项目已应用以下游戏工程最佳实践来提升操作手感：

### 1. 加速度模型而非直接速度

**问题**：使用 `speed = input * constant_value` 会导致操作生硬、与碰撞反馈冲突。

**解决**：改用
$$\Delta v = \text{input} \times \text{accel} \times dt$$
然后再应用阻尼，最后限速。这使得：
- 加速有"发力"过程
- 松手时会自然减速（根据阻尼衰减）
- 与碰撞速度变化叠加更平顺

### 2. 非对称阻尼

移动时与空闲时使用不同的阻尼系数：
- 移动阻尼 < 空闲阻尼 → 停下更快，更容易精确控制
- 相反的话会导致过度漂移

### 3. 固定物理步长

**问题**：按真实 dt 积分，不同帧率或偶发卡顿会导致物理结果不同，进而手感抖动。

**解决**：
- 固定间隔执行物理（1/120s）
- 用累积器处理帧时间
- 通过渲染阶段的位置插值补偿视觉离散感

**效果**：60fps、144fps 甚至掉帧后手感依然一致。

## 后续优化方向

1. **智能指针重构** - 把 `Ball` 和 `Windows` 中的裸指针改为 `std::unique_ptr`，减少内存泄漏风险
2. **参数可调化** - 把所有手感参数（加速度、阻尼、最大速度等）抽出配置文件，便于快速调参
3. **非对称加速** - 给玩家球单独加"转向加速更强、反向刹车更强"的曲线，提升竞技感
4. **输入缓冲** - 延迟处理输入，减少快速切换方向时的卡顿感
5. **视觉反馈** - 添加碰撞粒子、屏幕震动等反馈机制

## 文件职责总结

| 文件 | 职责 |
|------|------|
| `main.cpp` | 程序入口，初始化场景与主循环驱动 |
| `Ball.cpp/.hpp` | 小球属性与操作 |
| `Ball_Player.cpp/.hpp` | 玩家输入处理与控制模型 |
| `Physics.cpp/.hpp` | 碰撞、边界、物理规则 |
| `Windows.cpp/.hpp` | 窗口、渲染、固定步长循环 |
| `CMakeLists.txt` | 编译配置 |

## 许可与作者

Playground Project - 用于游戏编程学习与实践。
