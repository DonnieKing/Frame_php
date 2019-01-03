#include <stdio.h>
#include <algorithm>
#include <string.h>
#include <stdlib.h>
#define  MAX   100
#define maxsize 1000 //�������������
typedef struct pcb/*����*/
{
	int pcbID;		/*��������*/
	struct pcb *next;
}PCB;
 
typedef struct chct//ͨ�����Ʊ�
{
    int chctID;
    int status;//�豸״̬
    PCB *block;//��������
}CHCT;
 
typedef struct coct//���������Ʊ�
{
    int coctID;
    int status;//�豸״̬
    CHCT *chct;//�����������ӵ�ͨ��
    PCB *block;//��������
    struct coct *next;//����������
}COCT;
 
typedef struct dct//�豸���Ʊ�
{
    int dctID;
    int status;//�豸״̬
    int processid;//ռ�ý���ID
    PCB *block;//��������ָ��
    COCT *coct;//���豸������������Ŀ��������Ʊ�
    struct dct* next;//ͬ���豸�Ĳ�ͬ�豸
}DCT;
typedef struct sdt//ϵͳ�豸��
{
    char type;//ϵͳ�豸������
    char name[MAX];//ϵͳ�豸������
    DCT *dct;//DCT�豸���Ʊ�
    struct sdt *next;//������ڵ�ַ
}SDT;
/*����ȫ�ֱ���   3��ͨ����3���豸��������4���豸*/
CHCT *CH1,*CH2,*CH3;//����ͨ��ch1,ch2
COCT *coct_head;//���������Ʊ�ͷ��
SDT *sdt_head;
void init()
{
    PCB *ch1pcbblock,*ch2pcbblock,*ch3pcbblock,*co1pcbblock,
    *co2pcbblock,*co3pcbblock,
    *d1pcbblock,*d2pcbblock,
    *d3pcbblock,*d4pcbblock;//�����豸�ĵȴ�����
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
    //���������ʼʱ��ͨ���Ϳ��Ƶ��������
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
    //ͬ���豸����
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
    ����sdt���ҵ���Ӧ���豸��
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
    ��ʾ���е��豸��״̬
*/
void display(){
    SDT* sdttmp = sdt_head->next;
    DCT* dcttmp = NULL;
    printf("SDT   �豸ID  �豸״̬ ����COCT��ID  COCT״̬   ����CHCT��ID   CHCT״̬\n");
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
    ����豸
*/
void addDevice(){
    int channelid;//ͨ����
    printf("�����������豸������\n");
    char devicename[30];
    scanf("%s",devicename);
    SDT* cur = TravseSDT(devicename);
    DCT* pt = cur->dct;
    if(cur != sdt_head){//�����֪������豸
        while(pt->next!=NULL){
            pt=pt->next;
        }
        DCT* p = (DCT*)malloc(sizeof(DCT));
        pt->next = p;
        p->next = NULL;
        printf("�����������豸�ı�ʶ\n");
        scanf("%d",&p->dctID);
        p->status = 0;
        p->block = (PCB*)malloc(sizeof(PCB));
        p->coct = cur->dct->coct;
    }else{//����µ�������豸
        SDT* newsdt = (SDT*)malloc(sizeof(SDT));
        newsdt->next= sdt_head->next;
        sdt_head->next = newsdt;
        DCT* newdct = (DCT*)malloc(sizeof(SDT));
        newdct->dctID = 1;
        newdct->status=0;
        strcpy(newsdt->name,devicename);
        newsdt->dct=newdct;
        newdct->next = NULL;
        printf("������Ҫ����豸����������Ϣ:\n");
        COCT* con = (COCT*)malloc(sizeof(COCT));
        newdct->coct = con;
        con->next = coct_head->next;
        coct_head->next = con;
        printf("������������ı�ʶ\n");
        scanf("%d",&con->coctID);
        con->status=0;
      B:  printf("������Ҫʹ�õ�ͨ����\n");
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
        	printf("û�д�ͨ������\n");
           goto B;
        }
        con->block = (PCB*)malloc(sizeof(PCB));
    }
}
/**
    ɾ���豸
*/
void deleteDevice(){
    printf("������Ҫɾ�����豸����������\n");
    char deletename[30];
    scanf("%s",deletename);
    SDT* tmp = TravseSDT(deletename);//�ҵ������豸��sdt
    int i =1;
    if(tmp!=sdt_head){
        printf("������Ҫɾ���豸��ID\n");
        int deleteid;
        scanf("%d",&deleteid);
        DCT* cur = tmp->dct;
        while(cur != NULL){
            if(cur->dctID == deleteid && i==1){//ɾ���ҵ����豸ID��ɾ����һ���ڵ�
                tmp->dct = cur->next;
 
                break;
            }else if(cur->next->dctID == deleteid && cur->next->next != NULL){//�м�ڵ�
                DCT* p = cur->next;
                p->coct = NULL;
                cur->next = cur->next->next;
                free(p);
                break;
            }else if(cur->next->dctID == deleteid && cur->next->next == NULL){//���һ���ڵ�
                cur->next = NULL;
            }
            cur =  cur->next;
            i++;
        }
    }else{
        printf("�����豸������\n");
    }
 
}
/**
    �����豸
*/
void allotDevice(){
    PCB* pro = (PCB*)malloc(sizeof(PCB));
    printf("������̱�ʶ\n");
    scanf("%d",&pro->pcbID);
    pro->next = NULL;
    printf("������Ҫ������豸��������\n");
    char name[30];
    scanf("%s",name);
    //�ж����и����豸�Ƿ��п��е�
    SDT* p = sdt_head->next;
    DCT* pt = NULL;
    int flag=0;
    while(p!=NULL){
        if(strcmp(p->name,name) == 0){//�ҵ������豸
            pt = p->dct;
            while(pt!=NULL){
                if(pt->status == 0){//�豸����
                    pt->status =1;
                    flag = 1;
                    break;
                }
                pt = pt->next;
            }
            if(flag==1){
                if(pt->coct->status == 0){//�����豸��Ӧ���豸����������
                    pt->coct->status = 1;
                    if(pt->coct->chct->status == 0){//��Ӧ��ͨ������
                        pt->coct->chct->status =1;
                        printf("�豸����ɹ�\n");
                    }else{//������Ӧ��ͨ���ȴ�����
                        printf("ͨ��æµ\n");
                        PCB* newpcb = (PCB*)malloc(sizeof(PCB));
                        newpcb->next = pt->coct->chct->block->next;
                        pt->coct->chct->block->next = newpcb;
                    }
                }else{//������豸��Ӧ���豸�������ȴ�����
                    printf("�豸������æµ\n");
                    PCB* newpcb = (PCB*)malloc(sizeof(PCB));
                    newpcb->next = pt->coct->block->next;
                    pt->coct->block->next = newpcb;
                }
            }else{//�����豸�ȴ�����
                printf("�豸æµ\n");
                PCB* newpcb = (PCB*)malloc(sizeof(PCB));
                newpcb->next = pt->block->next;
                pt->block->next = newpcb;
            }
        }
        p = p->next;
    }
}
 
 
/**
    �����豸
*/
void reclaimDevice(){
    printf("������Ҫ���յ��豸����\n");
    char reclainname[30];
    scanf("%s",reclainname);
    int reclainID;//�����豸��
    SDT* p = sdt_head->next;
    DCT* pt = NULL;
    while(p!=NULL){
        if(strcmp(reclainname,p->name) == 0){//�ҵ������豸
            printf("������Ҫ���յ��豸ID\n");
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
//�Ƚ��ȳ������㷨
void FIFO(int array[],int m)
{
    int sum=0,j,i,now;
    float avg;
    printf("\n ----------------------------------\n");
    printf(" �����뵱ǰ�Ĵŵ��ţ�");
    scanf("%d",&now);
    printf("\n FIFO���Ƚ��:  ");
    printf("%d ",now);
    for(i=0; i<m; i++) printf("%d ",array[i]);
    sum=abs(now-array[0]);
    for(j=1; j<m; j++) sum+=abs(array[j]-array[j-1]); //�ۼ��ܵ��ƶ�����
    avg=(float)sum/m;//����ƽ��Ѱ������
    printf("\n �ƶ����ܵ����� %d \n",sum);
    printf(" ƽ��Ѱ�����ȣ� %.2f ",avg);
    printf("\n ----------------------------------\n");
}
 
//��̷���ʱ�����ȵ����㷨
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
        for(j=i+1; j<m; j++) //�Դŵ��Ž��д�С��������
        {
            if(array[i]>array[j])//���ŵ���֮��Ƚ�
            {
                temp=array[i];
                array[i]=array[j];
                array[j]=temp;
            }
        }
    }
    printf(" �����뵱ǰ�Ĵŵ��ţ�");
    scanf("%d",&now);
    printf("\n SSTF���Ƚ��:  ");
    if(array[m-1]<=now)//�ж���������������Ƿ�С�ڵ�ǰ�ŵ���
    {
        for(i=m-1; i>=0; i--) //������ŵ��ŴӴ�С���
            printf("%d  ",array[i]);
        sum=now-array[0];//�����ƶ�����
    }
    else if(array[0]>=now)//�ж���������������Ƿ񶼴��ڵ�ǰ�ŵ���
    {
        for(i=0; i<m; i++) //���ŵ��Ŵ�С�������
            printf("%d  ",array[i]);
        sum=array[m-1]-now;//�����ƶ�����
    }
    else
    {
        while(array[k]<now)//��һ�Ƚ���ȷ��Kֵ
        {
            k++;
        }
        l=k-1;
        r=k;
        //ȷ����ǰ�ŵ������ŵ������е�λ��
        while((l>=0)&&(r<m))
        {
            if((now-array[l])<=(array[r]-now))//�ж���̾���
            {
                printf("%d  ",array[l]);
                sum+=now-array[l];//�����ƶ�����
                now=array[l];
                l=l-1;
            }
            else
            {
                printf("%d  ",array[r]);
                sum+=array[r]-now;//�����ƶ�����
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
            sum+=array[m-1]-array[0];//�����ƶ�����
        }
        else
        {
            for(j=l; j>=0; j--)
            {
                printf("%d  ",array[j]);
            }
            sum+=array[m-1]-array[0];//�����ƶ�����
        }
    }
    avg=(float)sum/m;
    printf("\n �ƶ����ܵ����� %d \n",sum);
    printf(" ƽ��Ѱ�����ȣ� %.2f",avg);
    printf("\n ----------------------------------\n");
}
//ɨ������㷨�����ݵ����㷨��
void SCAN(int array[], int m)
{
    int now, fang;
    printf("\n ----------------------------------\n");
    printf(" �����뵱ǰ�Ĵŵ��ţ� ");
    scanf("%d",&now);
    printf("\n ��ѡ���ͷ�ƶ�����1.(����)��2.(�ݼ�)\n");
    printf("             ");
    scanf("%d",&fang);
    std::sort(array, array + m);
    int sum = 0;
    float avg;
    printf("\n FIFO ���Ƚ��: ");
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
        avg=(float)sum/m;//����ƽ��Ѱ������
        printf("\n �ƶ����ܵ����� %d \n",sum);
        printf(" ƽ��Ѱ�����ȣ� %f ",avg);
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
        avg=(float)sum/m;//����ƽ��Ѱ������
        printf("\n �ƶ����ܵ����� %d \n",sum);
        printf(" ƽ��Ѱ�����ȣ� %.2f ",avg);
    }
    printf("\n ----------------------------------\n");
}
//ѭ��ɨ���㷨 
void CSCAN(int array[], int m)
{
    int now, fang;
    printf("\n ----------------------------------\n");
    printf(" �����뵱ǰ�Ĵŵ��ţ� ");
    scanf("%d",&now);
    printf("\n ��ѡ���ͷ�ƶ�����1������2�ݼ�\n");
    printf("             ");
    scanf("%d", &fang);
    std::sort(array, array + m);
    int sum = 0;
    float avg;
    printf("\n FIFO ���Ƚ��: ");
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
        avg=(float)sum/m;//����ƽ��Ѱ������
        printf("\n �ƶ����ܵ����� %d \n",sum);
        printf(" ƽ��Ѱ�����ȣ� %.2f ",avg);
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
        avg=(float)sum/m;//����ƽ��Ѱ������
        printf("\n �ƶ����ܵ����� %d \n",sum);
        printf(" ƽ��Ѱ�����ȣ� %.2f ",avg);
    }
    printf("\n ----------------------------------\n");
}
 
 
// ��������
int main()
{
	int track;
A:	printf("-----------------------------------------\n");
	printf("--------�豸���估���̵���---------------\n"); 
	printf("-----------------------------------------\n");
	printf("--------------��ѡ��---------------------\n");
	printf("            1���豸����                   \n");
	printf("            2�����̵���                   \n");
	printf("            3���˳�                       \n");
    printf("-----------------------------------------\n");	
    printf("��ѡ��");
    scanf("%d",&track);
	switch(track)
	{
		case 1:while(1)	{
	init();
    display();
    int unit;
    while(1){
    	printf("-----------------------------------------\n");
        printf("---------------�豸����------------------\n");
        printf("             1:����豸                  \n");
        printf("             2:ɾ���豸                   \n");
        printf("             3:�����豸                  \n");
        printf("             4:�����豸                  \n");
        printf("             5:����������                \n");
        printf("  ��ѡ��  :");
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
    int cidao[maxsize];//����ŵ�������
    int i=0;
    int b;
    printf("\n ----------------------------------\n");
    printf("  ���̵����㷨ģ��");
    printf("\n ----------------------------------\n");
    printf("��������ŵ�������"); 
	scanf("%d",&b);
    printf("��������ŵ����У�");
    for(i=0; i<b; i++)
    {
        scanf("%d",&cidao[i]);
    }
    printf("\n �ŵ���ȡ�����");
    for(i=0; i<b; i++)
    {
        printf("%d  ",cidao[i]);//�����ȡ�Ĵŵ��Ĵŵ���
    }
    count=b;
    printf("\n           ");
    while(1)
    {
        printf("\n  �㷨ѡ��\n");
        printf(" 1���Ƚ��ȳ��㷨��FIFO��\n");
        printf(" 2����̷���ʱ�������㷨��SSTF��\n");
        printf(" 3��ɨ���㷨��SCAN��\n");
        printf(" 4��ѭ��ɨ���㷨��C-SCAN��\n");
        printf(" 5. �˳�\n");
        printf("\n");
        printf("��ѡ��");
        scanf("%d",&c);
        switch(c)//�㷨ѡ��
        {
        case 1:
            FIFO(cidao,count);//�Ƚ��ȳ��㷨
            printf("\n");
            break;
        case 2:
            SSTF(cidao,count);//��̷���ʱ�������㷨
            printf("\n");
            break;
        case 3:
            SCAN(cidao,count);//ɨ���㷨
            printf("\n");
            break;
        case 4:
            CSCAN(cidao,count);//ѭ��ɨ���㷨
            printf("\n");
            break;
        case 5:goto A;break;
         }
        
         }
    	break;
		} 
    }  
}

			
	
	


