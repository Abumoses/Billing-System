    #include <stdio.h>

struct item{
    char item[20];
    float price;
    int qty;
};

struct orders{
    char customer[20];
    char date[20];
    int numOfItem;
    struct item itm[50];
    
    
    
};

void generateBill_Header(char[],char[]);
void generateBill_Body(char[],int,float);
void generateBill_Footer(float);

int main(){
    int ch,i,n;
    FILE* fp;
    float total;
    struct orders ord;
    struct orders or;
    char saveBill;
    char name[20];
    int found = 0;
    start:
    do{
        system("clear");
        printf("%30s","ESTEC RESTAURANT\n");
        printf("\nChoose Your Operations");
        printf("\n1.Generate Invoice");
        printf("\n2.Show all Invoice");
        printf("\n3.Search Invoice");
        printf("\n0.Exist");
        printf("\n\nEnter Your choice: ");
        scanf("%d",&ch);
        
        switch(ch){
            case 1: 
            system("clear");
            printf("%30s","Generate Invoice\n");
            printf("\nEnter Customer Name: ");
            scanf(" %[^\n]s",ord.customer);
            strcpy(ord.date,__DATE__);
            printf("Enter Number of Items: ");
            scanf(" %d",&n);
            ord.numOfItem = n;
            
            for(i=0;i<n;i++){
                printf("\n");
                printf("Enter Item%d: ",i+1);
                scanf(" %s",ord.itm[i].item);
                printf("Please Enter the Quantity: ");
                scanf(" %d",&ord.itm[i].qty);
                printf("Enter the Unit Price: ");
                scanf(" %f",&ord.itm[i].price);
                total+=ord.itm[i].qty * ord.itm[i].price;
                
            }
            system("clear");
            generateBill_Header(ord.customer,ord.date);
            printf("\n%-15s%-17s%s","ITEM","QUANTITY","TOTAL");
            for(i=0;i<ord.numOfItem;i++)
                generateBill_Body(ord.itm[i].item,ord.itm[i].qty,ord.itm[i].price);
            generateBill_Footer(total);
            
            printf(" want to save the Invoice? [y/N]: ");
            scanf("%s",&saveBill);
            
            if(saveBill == 'y'){
                fp = fopen("esteh.txt","a");
                fwrite(&ord,sizeof(struct orders),1,fp);
                if(fwrite !=NULL){
                   system("clear");
                   printf("\nInvoice Successfully saved!");
                   
                }else{
                    printf("\nError saving");
                }     
                
                fclose(fp);      
            }
            printf("\npress 1 to continue..");
            scanf("%d",&ch);
            if(ch==1)
                goto start;
            
            break;
            case 2: 
                system("clear");
                printf("\n***********Previous Invoices************");
                fp=fopen("esteh.txt","r");
                while(fread(&or,sizeof(struct orders),1,fp)!=NULL){
                    float tot = 0;
                    generateBill_Header(or.customer, or.date);
                    printf("\n%-15s%-17s%s","ITEM","QUANTITY","TOTAL");
                    for(i=0;i<or.numOfItem;i++){
                        generateBill_Body(or.itm[i].item,or.itm[i].qty,or.itm[i].price);
                        tot += or.itm[i].qty * or.itm[i].price;
                    }
                    generateBill_Footer(tot);
                        
                }    
                printf("press 1 to continue..");
                scanf("%d",&ch);
                if(ch==1)
                    goto start;
                fclose(fp);   
            break;
            case 3:
                  system("clear");
                  printf("%28s","Search Invoice\n");
                  printf("\nEnter Customer Name to search: ");
                  scanf(" %[^\n]s",name);
                printf("\n**********Invoice of %s************",name);
                fp=fopen("esteh.txt","r");
                while(fread(&or,sizeof(struct orders),1,fp)!=NULL){
                    float tot = 0;
                    if(strcmp(or.customer,name)==0){
                        generateBill_Header(or.customer, or.date);
                        printf("\n%-15s%-17s%s","ITEM","QUANTITY","TOTAL");
                        for(i=0;i<or.numOfItem;i++){
                            generateBill_Body(or.itm[i].item,or.itm[i].qty,or.itm[i].price);
                            tot += or.itm[i].qty * or.itm[i].price;
                        }    
                        generateBill_Footer(tot);
                        found = 1;
                    }    
                    
                }    
                
                printf("\npress 1 to continue..");
                scanf(" %d",&ch);
                if(ch==1)
                    goto start;
                fclose(fp);
                
            break;
            case 0:
                printf("GOODBYE!!");
            break;    
        
        }
    
    }while(ch!=0);
}
//generate generateBill_Body
void generateBill_Header(char name[20],char date[20]){
        printf("\n\n");
        printf("%30s","ESTECH RESTAURANT");
        printf("\n***************************************");
        printf("\nDate:                        %s",date);
        printf("\nInvoic to:                   %s",name);
        printf("\n---------------------------------------");
        printf("\n");
    
}
//generate BillBody
void generateBill_Body(char itm[20], int qt,float pri){
        
        printf("\n%-18s%-14d%.2f",itm,qt,qt*pri);

}
//generate billfooter
void generateBill_Footer(float total){
    float dis = 0.1*total;
    float net_Total = total - dis;
    float cgst = 0.09*net_Total,grand_Total = net_Total+2*cgst;
    printf("\n\n---------------------------------------");
    printf("\nSub_Total\t\t\t%.2f",total);
    printf("\nDiscount @10%s\t\t\t%.2f","%",dis);
    printf("\nNet_Total\t\t\t%.2f","%",cgst);
    printf("\nSGSt @9% \t\t\t\t%.2f","%",cgst);
    printf("\n---------------------------------------");
    printf("\nGrand_Total\t\t\t%.2f",grand_Total);
    printf("\n---------------------------------------\n");
    printf("\n");

}

    