#排序
思路：
1.单趟
2.趟数／直接插入排序
#插入排序
思路：将一个数插入一个有序区间
时间复杂度
最好O(n) 最坏O(n^2)
最好：接近有序遍历一次数组
最坏：将升序排成降序
#希尔排序
是根据插入排序演化而来，当数据接近有序时数据的挪动次数会减少，这样会减下时间复杂度
时间复杂度；介于O(n)~O(n^2) 大约等于O(lg1.3)
1.预排序
2.gap=1相当于插入排序
ps:
```
while(gap < 1)//控制分组
	...
	for(size_t i = gap; i<size; i++)//这里是++i而不是i+=gap 表示每次并不是排一组数据而是多组数据同时进行，这样会加速有序
		...
		while(end >= 0)
		{
			a[end+gap] = a[end];//
		}
		...
```
#选择排序
思路：每次选择一个最小的和假设最小的比较，如果比假设的小，就交换
时间复杂度：最好最坏都是O(n^2) 交换趟数：n-1+n-2+....+1 
#选择排序的优化
思路：每次选择一个最小的和一个最大的假设最小的／最大的比较，如果比假设的小，就交换，如果比假设的大也交换。此时注意最大的数是否已经交换过了，如交换过了
```
if(max == left)
	max = min
```
时间复杂度：最好最坏还都是O(n^2) 交换趟数：n + n-4 + n-2 + ... +1
虽然一次选出了两个树但是并没有起到多到的优化作用
#堆排序O(lgn)
堆的性质：大堆堆顶元素最大，孩子都比它小，孩子不区分大小
升序 建大堆
1.建堆
2.调堆
堆是一个静态的二叉树
当抽象成二叉树的样子时，类似于层序遍历
下标：
		0
     1     2
   3  4  5  6
.................
例如：大堆
必须保证每一个子堆都是一个大堆(大的在堆顶)，于是会进行向下调整法
最后一个非叶子节点 (n-1-1)/2   n是个数 

调整完毕一趟，堆顶会是整个数组中最大的元素。将其与数组最后一个位置元素交换，然后调整，并每次少排一个数
#冒泡排序
与插入排序的比较：
当数组接近有序，选用插入排序更好，因为插入排序检测到有序会直接向数组后面插入，不挪动数据。而冒泡则对有序的要求比较严格，如果接近有序，冒泡还是会交换数据
#冒泡排序的优化
加入flag 标记交换否 减少交换次数
如果这个数组本来有序,在下一趟的比较中 将不再交换
#快速排序 时间O(nlgn) 空间O(lgn)
##方法1:左右指针法：
left->找大的  key(标记下标)   找小的<-right
1.选key 把key放到正确的位置 _<key<_
2.递归划分为子问题 左区间有序 右区间有序
3.注意当左右指针相遇时既找到了key的正确位置 交换a[key] a[left](此时left=right)
4.划分区间时key的位置已经排过，故还需要排的是[left,div-1]和[div+1,right]区间
##方法2:挖坑法
left->找大的  key(标记元素)   找小的<-right
1.left找大 left是坑 交换a[left] a[right]
2.right找小 right是坑 交换a[left] a[right]
3.最后的坑是right 把 key ＝a[right] 放在正确位置

##方法3:前后指针法 适用于链表
1.数组 下标既指针
key(标记元素)
cur ＝ left
prev = cur-1
2.cur找小
先++prev
交换a[cur] a[prev] (prev != cur)!!!
3.最后swap(a[++prev],a[right])
##三数取中法
为了每次取到的枢轴更接近于中点
##小区间优化法
减少压栈
当排序进行到一定程度 数组已经接近有序（right - left > 13） 这时用插入解决更快
##非递归
借助栈 减少压栈
##归并排序
1.假设整个数组有序
2.左右区间有序
3.划分子问题 递归
4.临时数组（空间消耗）存放暂时有序的数组
5.拷贝回原来的数组
ps:考虑一个10G数据进行排序 内存2G
思路:10G划分为1G(10个) 运用递归的思想 tmp1G 每次读1G 然后merge / 再读1G 再merge .....
	 比划分为10个1G 分别排 最后将这十个1G分别合并优－》减少文件读写次数
	创造例子：1000个int满了 每次读100个

##计数排序
统计字符串中第一次出现的字符
##基数排序
LSD 
桶
