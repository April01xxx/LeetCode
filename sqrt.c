/**
 * Implement int sqrt(int x).
 * Compute and return the square root of x, where x is guaranteed to be a 
 * non-negative integer. Since the return type is an integer, the decimal 
 * digits are truncated and only the integer part of the result is returned.
 *
 * Example:
 *   Input: 8
 *   Output: 2
 *
 * 实现求平方根,注意返回结果要截断为整数.基本思想是利用牛顿迭代法.不过有一种快速
 * 求平方根的方法利用了一个magic number,使得收敛的速度巨增从而提高了计算速度.
 * 先来看看牛顿迭代法的基本思想:要求一个正整数a的平方根,也就是求解方程x^2-a=0
 * 的正根.牛顿迭代法的基础是泰勒级数,令f(x)=x^2-a,要求解f(x)=0的根,我们利用f(x)
 * 泰勒展开的一次项,忽略高阶项,得到f(x)=f(x0)+f'(x0)(x-x0).于是问题转换为求解
 * f(x0)+f'(x0)(x-x0)=0的解,这样的得到的结果往往不够精确,重复迭代可以缩小误差.
 * 例如求解x^2 = 10的解(3.1622776601683793319988935444327).
 * 任意选取x0=5,于是25-10+10(x-5)=0,得到x1=3.5,将x1代入公式
 * X_n+1 = (Xn*Xn + a) / (2*Xn),得到x2≈3.17,...,x3=3.162.
 * 可以发现已经很接近答案.
 * 关于初始值的选取,上面的计算过程是简单的取了原值的二分之一,但有一种非常快速的
 * 方法,详细的内容可以Google搜索fast inverse square root.
 * https://en.wikipedia.org/wiki/Fast_inverse_square_root
 * https://blog.csdn.net/qq_21201963/article/details/80174155
 */
int
mySqrt(int x) {
  double x0, x1;  /* 这里如果是float类型,若x=2147395599则得到错误结果. */

  if (x <= 0)
    return 0;

  x0 = x;
  x1 = (x0 + 1) / 2;
  /* 因为返回结果为截断的整数,这里的精度控制为0.9就可以了. */
  while (x0 - x1 > 0.9 || x0 - x1 < -0.9) {
    x0 = x1;
    x1 = (x0 + x / x0) / 2;
  }
  return (int)x1;
}

/**
 * 上述代码可以简化.
 */
int
mySqrt(int x) {
  long long ans;  /* 防止下面计算平方时溢出. */

  ans = x;
  while (ans * ans > x)
    ans = (ans + x / ans) / 2;
  return (int)ans;
}

/**
 * 用double来保存平方,用一个变量保存中间值避免计算两次平方.
 */
int
mySqrt(int x) {
  double ans, tmp;  /* 防止下面计算平方时溢出. */

  ans = x;
  tmp = ans * ans;
  while (tmp - x > 0.9 || tmp - x < -0.9) {
    ans = (ans + x / ans) / 2;
    tmp = ans * ans;
  }
  return (int)ans;
}