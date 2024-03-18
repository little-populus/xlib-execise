# 学习笔记

---

该仓库记录了学习Xlib过程的代码和心得

---

## 一些X11遇到的问题解决方案

---

如果遇到了

```bash
sudo apt install libx11-dev libxext-dev libxtst-dev libxrender-dev libxmu-dev libxmuu-dev

下列软件包有未满足的依赖关系：
 libx11-dev : 依赖: libx11-6 (= 2:1.6.12.4-deepin1) 但是 2:1.6.12.5-deepin1 正要被安装

 The following packages have unmet dependencies:
 libx11-dev : Depends: libx11-6 (= 2:1.6.12.4-deepin1) but 2:1.6.12.5-deepin1 is to be installed
```

可以尝试使用

```bash
sudo apt install libx11-6=2:1.6.12.4-deepin1
```

然后再执行原指令即可

---

编译gcc时遇到

```bash
/usr/bin/ld: final link failed: nonrepresentable section on output
collect2: error: ld returned 1 exit status
```

根据网上的解决方案只需要在编译选项中加入`-fPIC`即可