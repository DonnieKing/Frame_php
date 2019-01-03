#include <stdio.h>
#include <algorithm>
#include <string.h>
#include <stdlib.h>
#define  MAX   100
#define maxsize 1000 //定义最大数组域
typedef struct pcb/*进程*/
{
	int pcbID;		/*进程名称*/
	struct pcb *next;
}PCB;
 
typedef struct chct//通道控制表
{
    int chctID;
    int status;//设备状态
    PCB *block;//阻塞队列
}CHCT;
 
typedef struct coct//控制器控制表
{
    int coctID;
    int status;//设备状态
    CHCT *chct;//控制器所连接的通道
    PCB *block;//阻塞队列
    struct coct *next;//控制器队列
}COCT;
 
typedef struct dct//设备控制表
{
    int dctID;
    int status;//设备状态
    int processid;//占用进程ID
    PCB *block;//阻塞队列指针
    COCT *coct;//与设备控制器相关连的控制器控制表
    struct dct* next;//同类设备的不同设备
}DCT;
typedef struct sdt//系统设备表
{
    char type;//系统设备表类型
    char name[MAX];//系统设备表名称
    DCT *dct;//DCT设备控制表
    struct sdt *next;//驱动入口地址
}SDT;
/*设置全局变量   3个通道、3个设备控制器、4个设备*/
CHCT *CH1,*CH2,*CH3;//两个通道ch1,ch2
COCT *coct_head;//控制器控制表头部
SDT *sdt_head;
void init()
{
    PCB *ch1pcbblock,*ch2pcbblock,*ch3pcbblock,*co1pcbblock,
    *co2pcbblock,*co3pcbblock,
    *d1pcbblock,*d2pcbblock,
    *d3pcbblock,*d4pcbblock;//各个设备的等待队列
    COCT*CO1,*CO2,*CO3;
    DCT *dct1,*dct2,*dct3,*dct4;
    SDT *sdt1,*sdt2,*sdt3,*sdt4;
    CH1=(CHCT*)malloc(sizeof(CHCT));
    CH2=(CHCT*)malloc(sizeof(CHCT));
    CH3=(CHCT*)malloc(sizeof(CHCT));
    CH1->status=0;
    CH2->status=0;
    CH3->status=0;
    CH1->chctID = 1;
    CH2->chctID = 2;
    CH3->chctID = 3;
    ch1pcbblock=(PCB*)malloc(sizeof(PCB));
    ch2pcbblock=(PCB*)malloc(sizeof(PCB));
    ch3pcbblock=(PCB*)malloc(sizeof(PCB));
    ch1pcbblock->next=NULL;
    ch2pcbblock->next=NULL;
    ch3pcbblock->next=NULL;
    CH1->block=ch1pcbblock;
    CH2->block=ch2pcbblock;
    CH3->block=ch3pcbblock;
    coct_head=(COCT*)malloc(sizeof(COCT));
    coct_head->next=NULL;
    CO1=(COCT*)malloc(sizeof(COCT));
    CO2=(COCT*)malloc(sizeof(COCT));
    CO3=(COCT*)malloc(sizeof(COCT));
    CO1->status=0;
    CO2->status=0;
    CO3->status=0;
    coct_head->next=CO1;
    CO1->next=CO2;
    CO2->next=CO3;
    CO3->next=NULL;
    co1pcbblock=(PCB *)malloc(sizeof(PCB));
    co1pcbblock->next=NULL;
    co2pcbblock=(PCB *)malloc(sizeof(PCB));
    co2pcbblock->next=NULL;
    co3pcbblock=(PCB *)malloc(sizeof(PCB));
    co3pcbblock->next=NULL;
    CO1->coctID = 1;
    CO2->coctID = 2;
    CO3->coctID = 3;
    //随机分配起始时的通道和控制的连接情况
    CO1->chct=CH1;
    CO2->chct=CH1;
    CO3->chct=CH2;
    CO1->block=co1pcbblock;
    CO2->block=co2pcbblock;
    CO3->block=co3pcbblock;
 
    d1pcbblock=(PCB *)malloc(sizeof(PCB));
    d2pcbblock=(PCB *)malloc(sizeof(PCB));
    d3pcbblock=(PCB *)malloc(sizeof(PCB));
    d4pcbblock=(PCB *)malloc(sizeof(PCB));
    d1pcbblock->next=NULL;
    d2pcbblock->next=NULL;
    d3pcbblock->next=NULL;
    d3pcbblock->next=NULL;
 
    dct1=(DCT *)malloc(sizeof(DCT));
    dct2=(DCT *)malloc(sizeof(DCT));
    dct3=(DCT *)malloc(sizeof(DCT));
    dct4=(DCT *)malloc(sizeof(DCT));
    dct1->dctID = 1;
    dct2->dctID = 1;
    dct3->dctID = 1;
    dct4->dctID = 1;
    dct1->coct=CO1;
    dct2->coct=CO2;
    dct3->coct=CO3;
    dct4->coct=CO3;
    dct1->status=0;
    dct2->status=0;
    dct3->status=0;
    dct4->status=0;
    //同类设备链表
    dct1->next = NULL;
    dct2->next = NULL;
    dct3->next = NULL;
    dct4->next = NULL;
    dct1->block=d1pcbblock;
    dct2->block=d2pcbblock;
    dct3->block=d3pcbblock;
    dct4->block=d4pcbblock;
    sdt_head=(SDT *)malloc(sizeof(SDT));
    sdt_head->next=NULL;
    sdt1=(SDT *)malloc(sizeof(SDT));
    sdt2=(SDT *)malloc(sizeof(SDT));
    sdt3=(SDT *)malloc(sizeof(SDT));
    sdt4=(SDT *)malloc(sizeof(SDT));
    sdt_head->next=sdt1;
    sdt1->next=sdt2;
    sdt2->next=sdt3;
    sdt3->next=sdt4;
    sdt4->next = NULL;
    strcpy(sdt1->name,"printer");
    strcpy(sdt2->name,"screen");
    strcpy(sdt3->name,"keyboad");
    strcpy(sdt4->name,"mouse");
    sdt1->dct=dct1;
    sdt2->dct=dct2;
    sdt3->dct=dct3;
    sdt4->dct=dct4;
}
/**
    遍历sdt表，找到相应的设备类
*/
SDT* TravseSDT(char searchname[]){
    SDT* tmp;
    tmp = sdt_head->next;
    while(tmp!=NULL){
//        printf("%s\n",tmp->name);
        if(strcmp(tmp->name,searchname) == 0){
            printf("a:%s\n",tmp->name);
            return tmp;
        }
        tmp = tmp->next;
    }
    return sdt_head;
}
/**
    显示所有的设备及状态
*/
void display(){
    SDT* sdttmp = sdt_head->next;
    DCT* dcttmp = NULL;
    printf("SDT   设备ID  设备状态 所连COCT的ID  COCT状态   所连CHCT的ID   CHCT状态\n");
    while(sdttmp != NULL){
        dcttmp = sdttmp->dct;
        while(dcttmp != NULL){
            printf("%s\t%d\t%d         %d            %d             %d         %d\n",sdttmp->name,dcttmp->dctID,dcttmp->status,dcttmp->coct->coctID,dcttmp->coct->status,dcttmp->coct->chct->chctID,dcttmp->coct->chct->status);
            dcttmp = dcttmp->next;
        }
        sdttmp = sdttmp->next;
    }
}
 
/**
void displaySDT(){
    SDT* p = sdt_head->next;
    while(p!=NULL){
        printf("%s\n",p->name);
        p = p->next;
    }
}
*/
 
/**
    添加设备
*/
void addDevice(){
    int channelid;//通道号
    printf("请输入待添加设备的名称\n");
    char devicename[30];
    scanf("%s",devicename);
    SDT* cur = TravseSDT(devicename);
    DCT* pt = cur->dct;
    if(cur != sdt_head){//添加已知种类的设备
        while(pt->next!=NULL){
            pt=pt->next;
        }
        DCT* p = (DCT*)malloc(sizeof(DCT));
        pt->next = p;
        p->next = NULL;
        printf("请输入待添加设备的标识\n");
        scanf("%d",&p->dctID);
        p->status = 0;
        p->block = (PCB*)malloc(sizeof(PCB));
        p->coct = cur->dct->coct;
    }else{//添加新的种类的设备
        SDT* newsdt = (SDT*)malloc(sizeof(SDT));
        newsdt->next= sdt_head->next;
        sdt_head->next = newsdt;
        DCT* newdct = (DCT*)malloc(sizeof(SDT));
        newdct->dctID = 1;
        newdct->status=0;
        strcpy(newsdt->name,devicename);
        newsdt->dct=newdct;
        newdct->next = NULL;
        printf("请输入要添加设备控制器的信息:\n");
        COCT* con = (COCT*)malloc(sizeof(COCT));
        newdct->coct = con;
        con->next = coct_head->next;
        coct_head->next = con;
        printf("请输入控制器的标识\n");
        scanf("%d",&con->coctID);
        con->status=0;
      B:  printf("请输入要使用的通道号\n");
        scanf("%d",&channelid);
        if(channelid == 1){
            con->chct = CH1;
        }
        if(channelid == 2){
            con->chct = CH2;
        }
         if(channelid == 3){
            con->chct = CH3;
        }if(channelid > 3){
        	printf("没有此通道！！\n");
           goto B;
        }
        con->block = (PCB*)malloc(sizeof(PCB));
    }
}
/**
    删除设备
*/
void deleteDevice(){
    printf("请输入要删除的设备的种类名称\n");
    char deletename[30];
    scanf("%s",deletename);
    SDT* tmp = TravseSDT(deletename);//找到该类设备的sdt
    int i =1;
    if(tmp!=sdt_head){
        printf("请输入要删除设备的ID\n");
        int deleteid;
        scanf("%d",&deleteid);
        DCT* cur = tmp->dct;
        while(cur != NULL){
            if(cur->dctID == deleteid && i==1){//删除找到的设备ID，删除第一个节点
                tmp->dct = cur->next;
 
                break;
            }else if(cur->next->dctID == deleteid && cur->next->next != NULL){//中间节点
                DCT* p = cur->next;
                p->coct = NULL;
                cur->next = cur->next->next;
                free(p);
                break;
            }else if(cur->next->dctID == deleteid && cur->next->next == NULL){//最后一个节点
                cur->next = NULL;
            }
            cur =  cur->next;
            i++;
        }
    }else{
        printf("该类设备不存在\n");
    }
 
}
/**
    分配设备
*/
void allotDevice(){
    PCB* pro = (PCB*)malloc(sizeof(PCB));
    printf("输入进程标识\n");
    scanf("%d",&pro->pcbID);
    pro->next = NULL;
    printf("请输入要申请的设备种类名称\n");
    char name[30];
    scanf("%s",name);
    //判断所有该类设备是否有空闲的
    SDT* p = sdt_head->next;
    DCT* pt = NULL;
    int flag=0;
    while(p!=NULL){
        if(strcmp(p->name,name) == 0){//找到该类设备
            pt = p->dct;
            while(pt!=NULL){
                if(pt->status == 0){//设备可用
                    pt->status =1;
                    flag = 1;
                    break;
                }
                pt = pt->next;
            }
            if(flag==1){
                if(pt->coct->status == 0){//该类设备对应的设备控制器可用
                    pt->coct->status = 1;
                    if(pt->coct->chct->status == 0){//相应的通道可用
                        pt->coct->chct->status =1;
                        printf("设备分配成功\n");
                    }else{//进入相应的通道等待队列
                        printf("通道忙碌\n");
                        PCB* newpcb = (PCB*)malloc(sizeof(PCB));
                        newpcb->next = pt->coct->chct->block->next;
                        pt->coct->chct->block->next = newpcb;
                    }
                }else{//进入该设备相应的设备控制器等待队列
                    printf("设备控制器忙碌\n");
                    PCB* newpcb = (PCB*)malloc(sizeof(PCB));
                    newpcb->next = pt->coct->block->next;
                    pt->coct->block->next = newpcb;
                }
            }else{//进入设备等待队列
                printf("设备忙碌\n");
                PCB* newpcb = (PCB*)malloc(sizeof(PCB));
                newpcb->next = pt->block->next;
                pt->block->next = newpcb;
            }
        }
        p = p->next;
    }
}
 
 
/**
    回收设备
*/
void reclaimDevice(){
    printf("请输入要回收的设备种类\n");
    char reclainname[30];
    scanf("%s",reclainname);
    int reclainID;//回收设备号
    SDT* p = sdt_head->next;
    DCT* pt = NULL;
    while(p!=NULL){
        if(strcmp(reclainname,p->name) == 0){//找到该类设备
            printf("请输入要回收的设备ID\n");
            scanf("%d",&reclainID);
            pt = p->dct;
            while(pt!=NULL){
                if(pt->dctID == reclainID){
                    pt->status=0;
//                    pt->coct->status =0;
//                    pt->coct->chct->status = 0;
                }
                pt=pt->next;
            }
        }
        p = p->next;
    }
}
//先进先出调度算法
void FIFO(int array[],int m)
{
    int sum=0,j,i,now;
    float avg;
    printf("\n ----------------------------------\n");
    printf(" 请输入当前的磁道号：");
    scanf("%d",&now);
    printf("\n FIFO调度结果:  ");
    printf("%d ",now);
    for(i=0; i<m; i++) printf("%d ",array[i]);
    sum=abs(now-array[0]);
    for(j=1; j<m; j++) sum+=abs(array[j]-array[j-1]); //累计总的移动距离
    avg=(float)sum/m;//计算平均寻道长度
    printf("\n 移动的总道数： %d \n",sum);
    printf(" 平均寻道长度： %.2f ",avg);
    printf("\n ----------------------------------\n");
}
 
//最短服务时间优先调度算法
void SSTF(int array[],int m)
{
    int temp;
    int k=1;
    int now,l,r;
    int i,j,sum=0;
    float avg;
    printf("\n ----------------------------------\n");
    for(i=0; i<m; i++)
    {
        for(j=i+1; j<m; j++) //对磁道号进行从小到大排列
        {
            if(array[i]>array[j])//两磁道号之间比较
            {
                temp=array[i];
                array[i]=array[j];
                array[j]=temp;
            }
        }
    }
    printf(" 请输入当前的磁道号：");
    scanf("%d",&now);
    printf("\n SSTF调度结果:  ");
    if(array[m-1]<=now)//判断整个数组里的数是否都小于当前磁道号
    {
        for(i=m-1; i>=0; i--) //将数组磁道号从大到小输出
            printf("%d  ",array[i]);
        sum=now-array[0];//计算移动距离
    }
    else if(array[0]>=now)//判断整个数组里的数是否都大于当前磁道号
    {
        for(i=0; i<m; i++) //将磁道号从小到大输出
            printf("%d  ",array[i]);
        sum=array[m-1]-now;//计算移动距离
    }
    else
    {
        while(array[k]<now)//逐一比较以确定K值
        {
            k++;
        }
        l=k-1;
        r=k;
        //确定当前磁道在已排的序列中的位置
        while((l>=0)&&(r<m))
        {
            if((now-array[l])<=(array[r]-now))//判断最短距离
            {
                printf("%d  ",array[l]);
                sum+=now-array[l];//计算移动距离
                now=array[l];
                l=l-1;
            }
            else
            {
                printf("%d  ",array[r]);
                sum+=array[r]-now;//计算移动距离
                now=array[r];
                r=r+1;
            }
        }
        if(l==-1)
        {
            for(j=r; j<m; j++)
            {
                printf("%d  ",array[j]);
            }
            sum+=array[m-1]-array[0];//计算移动距离
        }
        else
        {
            for(j=l; j>=0; j--)
            {
                printf("%d  ",array[j]);
            }
            sum+=array[m-1]-array[0];//计算移动距离
        }
    }
    avg=(float)sum/m;
    printf("\n 移动的总道数： %d \n",sum);
    printf(" 平均寻道长度： %.2f",avg);
    printf("\n ----------------------------------\n");
}
//扫描调度算法（电梯调度算法）
void SCAN(int array[], int m)
{
    int now, fang;
    printf("\n ----------------------------------\n");
    printf(" 请输入当前的磁道号： ");
    scanf("%d",&now);
    printf("\n 请选择刺头移动方向：1.(递增)，2.(递减)\n");
    printf("             ");
    scanf("%d",&fang);
    std::sort(array, array + m);
    int sum = 0;
    float avg;
    printf("\n FIFO 调度结果: ");
    if(fang == 1)
    {
        int index = std::lower_bound(array, array + m, now) - array;
        for(int i = index; i < m; i++)
        {
            sum += abs(now - array[i]);
            now = array[i];
            printf("%d ", array[i]);
        }
        for(int i = index - 1; i >= 0; i--)
        {
            sum += abs(now - array[i]);
            now = array[i];
            printf("%d ", array[i]);
        }
        avg=(float)sum/m;//计算平均寻道长度
        printf("\n 移动的总道数： %d \n",sum);
        printf(" 平均寻道长度： %f ",avg);
    }
    else
    {
        int index = std::lower_bound(array, array + m, now) - array;
        for(int i = index - 1; i >= 0; i--)
        {
            sum += abs(now - array[i]);
            now = array[i];
            printf("%d ", array[i]);
        }
        for(int i = index; i < m; i++)
        {
            sum += abs(now - array[i]);
            now = array[i];
            printf("%d ", array[i]);
        }
        avg=(float)sum/m;//计算平均寻道长度
        printf("\n 移动的总道数： %d \n",sum);
        printf(" 平均寻道长度： %.2f ",avg);
    }
    printf("\n ----------------------------------\n");
}
//循环扫描算法 
void CSCAN(int array[], int m)
{
    int now, fang;
    printf("\n ----------------------------------\n");
    printf(" 请输入当前的磁道号： ");
    scanf("%d",&now);
    printf("\n 请选择刺头移动方向：1递增，2递减\n");
    printf("             ");
    scanf("%d", &fang);
    std::sort(array, array + m);
    int sum = 0;
    float avg;
    printf("\n FIFO 调度结果: ");
    if(fang == 1)
    {
        int index = std::lower_bound(array, array + m, now) - array;
        for(int i = index; i < m; i++)
        {
            sum += abs(now - array[i]);
            now = array[i];
            printf("%d ", array[i]);
        }
        for(int i = 0; i < index; i++)
        {
            sum += abs(now - array[i]);
            now = array[i];
            printf("%d ", array[i]);
        }
        avg=(float)sum/m;//计算平均寻道长度
        printf("\n 移动的总道数： %d \n",sum);
        printf(" 平均寻道长度： %.2f ",avg);
    }
    else
    {
        int index = std::lower_bound(array, array + m, now) - array;
        for(int i = index - 1; i >= 0; i--)
        {
            sum += abs(now - array[i]);
            now = array[i];
            printf("%d ", array[i]);
        }
        for(int i = m - 1; i >= index; i--)
        {
            sum += abs(now - array[i]);
            now = array[i];
            printf("%d ", array[i]);
        }
        avg=(float)sum/m;//计算平均寻道长度
        printf("\n 移动的总道数： %d \n",sum);
        printf(" 平均寻道长度： %.2f ",avg);
    }
    printf("\n ----------------------------------\n");
}
 
 
// 操作界面
int main()
{
	int track;
A:	printf("-----------------------------------------\n");
	printf("--------设备分配及磁盘调度---------------\n"); 
	printf("-----------------------------------------\n");
	printf("--------------请选择---------------------\n");
	printf("            1、设备分配                   \n");
	printf("            2、磁盘调度                   \n");
	printf("            3、退出                       \n");
    printf("-----------------------------------------\n");	
    printf("请选择：");
    scanf("%d",&track);
	switch(track)
	{
		case 1:while(1)	{
	init();
    display();
    int unit;
    while(1){
    	printf("-----------------------------------------\n");
        printf("---------------设备分配------------------\n");
        printf("             1:添加设备                  \n");
        printf("             2:删除设备                   \n");
        printf("             3:分配设备                  \n");
        printf("             4:回收设备                  \n");
        printf("             5:返回主界面                \n");
        printf("  请选择  :");
        scanf("%d",&unit);
        if(unit == 1){
            addDevice();
            display();
        }else if(unit == 2){
            deleteDevice();
            display();
        }else if(unit == 3){
            allotDevice();
            display();
        }else if(unit == 4){
            reclaimDevice(); 
            display();
        }else{
		  goto A ;break;
		}
    }	
			break;
		}
			case 2:while(1){	
    int c;
    int count;
    //int m=0;
    int cidao[maxsize];//定义磁道号数组
    int i=0;
    int b;
    printf("\n ----------------------------------\n");
    printf("  磁盘调度算法模拟");
    printf("\n ----------------------------------\n");
    printf("请先输入磁道数量："); 
	scanf("%d",&b);
    printf("请先输入磁道序列：");
    for(i=0; i<b; i++)
    {
        scanf("%d",&cidao[i]);
    }
    printf("\n 磁道读取结果：");
    for(i=0; i<b; i++)
    {
        printf("%d  ",cidao[i]);//输出读取的磁道的磁道号
    }
    count=b;
    printf("\n           ");
    while(1)
    {
        printf("\n  算法选择：\n");
        printf(" 1、先进先出算法（FIFO）\n");
        printf(" 2、最短服务时间优先算法（SSTF）\n");
        printf(" 3、扫描算法（SCAN）\n");
        printf(" 4、循环扫描算法（C-SCAN）\n");
        printf(" 5. 退出\n");
        printf("\n");
        printf("请选择：");
        scanf("%d",&c);
        switch(c)//算法选择
        {
        case 1:
            FIFO(cidao,count);//先进先出算法
            printf("\n");
            break;
        case 2:
            SSTF(cidao,count);//最短服务时间优先算法
            printf("\n");
            break;
        case 3:
            SCAN(cidao,count);//扫描算法
            printf("\n");
            break;
        case 4:
            CSCAN(cidao,count);//循环扫描算法
            printf("\n");
            break;
        case 5:goto A;break;
         }
        
         }
    	break;
		} 
    }  
}

			
	
	


