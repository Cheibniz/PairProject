# PairProject
BUAA SE Pair Project

实现一个能求解简单几何形状之间交点的软件。

#### 运行说明

##### 命令行使用：

```
intersect.exe -i <path to input file> -o <path to output file>
```

使用命令行输入文件的路径，如：

```
intersect.exe -i input.txt -o output.txt
```

##### GUI使用：

运行bin/MFCGUI.exe可以直接运行GUI程序，注意需要将exe文件与core.dll文件放在同一目录下。

初学GUI，很多功能实现的不够人性化，比如在调节刻度大小时需要先关闭绘图窗口，使用时请注意。

##### 编译项目：

要正确编译项目，请运行include下的exe文件，安装用到的图形库。该库将windowsAPI进行了再次封装，只在编译时需要链接，直接运行GUI.exe文件则不需要。