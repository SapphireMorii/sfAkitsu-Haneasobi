# sfAkitsu-Haneasobi #

C++项目

注意：
- 使用Cmake编译

- 必须下载和使用GCC 7.3.0 x86_64

地址为：https://sourceforge.net/projects/mingw-w64/files/Toolchains%20targetting%20Win64/Personal%20Builds/mingw-builds/7.3.0/threads-posix/seh/x86_64-7.3.0-release-posix-seh-rt_v5-rev0.7z/download

- 记得把src目录下的Fonts、Levels、Music文件夹放到Cmake生成的Build目录中，同时把SFML-2.5.1/bin目录下的动态链接库页拷贝过去

TODO：
- ~~小球撞击到板的侧面时，按照球的速度方向反弹~~

- ~~小球从下方撞击到板时，应当直接穿过~~

- ~~添加连击数~~

- 给板一个加速能力：例如连按两次有加速效果

- 砖块所剩不多时，板发射子弹

- 元素反应实现
    - 冻结：球与砖块发生冻结反应时，相邻的同类型砖块一并冻结并一起被击碎
    - 超载：球与砖块发生超载或者球处于超载状态撞击砖块时，对周围的砖块也造成伤害
    - 感电： 球与砖块发生感电或球处于感电状态撞击砖块时，最周围方块随机造成伤害并附加雷元素（若板块为冰元素被赋予雷元素怎么办？）

- 关卡设计：增加更多关卡，并设计关卡选择界面

- 界面美化（音效）：界面、游戏元素美术优化

- buff设计
    - 球分裂

    - 球加速

    - 板增长

    - 下方出现临时墙

    - 速度加快

    - 强化子弹