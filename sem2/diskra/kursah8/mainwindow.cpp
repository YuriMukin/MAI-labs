#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QDebug>
QString input_info, output, decode, outputd="";

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void askii_to_char(long int l1)
{
                if (l1==100100000)
                    outputd+=" ";
                if (l1==100110000)
                    outputd+="0";
                if (l1==100110001)
                    outputd+="1";
                if (l1==100110010)
                    outputd+="2";
                if (l1==100110011)
                    outputd+="3";
                if (l1==100110100)
                    outputd+="4";
                if (l1==100110101)
                    outputd+="5";
                if (l1==100110110)
                    outputd+="6";
                if (l1==100110111)
                    outputd+="7";
                if (l1==100111000)
                    outputd+="8";
                if (l1==100111001)
                    outputd+="9";
                if (l1==100101011)
                    outputd+="+";
                if (l1==100101111)
                    outputd+="/";
                if (l1==100101010)
                    outputd+="*";
                if (l1==100101000)
                    outputd+="(";
                if (l1==100101001)
                    outputd+=")";
                if (l1==100111101)
                    outputd+="=";
                if (l1==100101110)
                    outputd+=".";
                if (l1==100101100)
                    outputd+=",";
                if (l1==100100001)
                    outputd+="!";
                if (l1==100111111)
                    outputd+="?";
                if (l1==100101101)
                    outputd+="-";
                if (l1==100111010)
                    outputd+=":";
                if (l1==100111011)
                    outputd+=";";
                if (l1==101100001)
                    outputd+="a";//outputd+=1011000010;
                if (l1==101100010)
                    outputd+="b";//outputd+=101100010;
                if (l1==101100011)
                    outputd+="c";
                if (l1==101100100)
                    outputd+="d";
                if (l1==101100101)
                    outputd+="e";
                if (l1==101100110)
                    outputd+="f";
                if (l1==101100111)
                    outputd+="g";
                if (l1==101101000)
                    outputd+="h";//outputd+=101101000;
                if (l1==101101001)
                    outputd+="i";
                if (l1==101101010)
                    outputd+="j";
                if (l1==101101011)
                    outputd+="k";
                if (l1==101101100)
                    outputd+="l";
                if (l1==101101101)
                    outputd+="m";
                if (l1==101101110)
                    outputd+="n";
                if (l1==101101111)
                    outputd+="o";
                if (l1==101110000)
                    outputd+="p";
                if (l1==101110001)
                    outputd+="q";
                if (l1==101110010)
                    outputd+="r";//outputd+=101110010;
                if (l1==101110011)
                    outputd+="s";
                if (l1==101110100)
                    outputd+="t";
                if (l1==101110101)
                    outputd+="u";
                if (l1==101110110)
                    outputd+="v";
                if (l1==101110111)
                    outputd+="w";
                if (l1==101111000)
                    outputd+="x";
                if (l1==101111001)
                    outputd+="y";
                if (l1==101111010)
                    outputd+="z";
}

unsigned long long char_to_aski(long int l1)
{
    unsigned long long a=0;
                if (l1==' ')
                    a+=100100000;
                if (l1=='+')
                    a+=100101011;
                if (l1=='/')
                    a+=100101111;
                if (l1=='*')
                    a+=100101010;
                if (l1=='(')
                    a+=100101000;
                if (l1==')')
                    a+=100101001;
                if (l1=='=')
                    a+=100111101;
                if (l1=='0')
                    a+=100110000;
                if (l1=='1')
                    a+=100110001;
                if (l1=='2')
                    a+=100110010;
                if (l1=='3')
                    a+=100110011;
                if (l1=='4')
                    a+=100110100;
                if (l1=='5')
                    a+=100110101;
                if (l1=='6')
                    a+=100110110;
                if (l1=='7')
                    a+=100110111;
                if (l1=='8')
                    a+=100111000;
                if (l1=='9')
                    a+=100111001;
                if (l1=='.')
                    a+=100101110;
                if (l1==',')
                    a+=100101100;
                if (l1=='!')
                    a+=100100001;
                if (l1=='?')
                    a+=100111111;
                if (l1=='-')
                    a+=100101101;
                if (l1==':')
                    a+=100111010;
                if (l1==';')
                    a+=100111011;
                if (l1=='a')
                    a+=101100001;//a+=1011000010;
                if (l1=='b')
                    a+=101100010;//a+=101100010;
                if (l1=='c')
                    a+=101100011;
                if (l1=='d')
                    a+=101100100;
                if (l1=='e')
                    a+=101100101;
                if (l1=='f')
                    a+=101100110;
                if (l1=='g')
                    a+=101100111;
                if (l1=='h')
                    a+=101101000;//a+=101101000;
                if (l1=='i')
                    a+=101101001;
                if (l1=='j')
                    a+=101101010;
                if (l1=='k')
                    a+=101101011;
                if (l1=='l')
                    a+=101101100;
                if (l1=='m')
                    a+=101101101;
                if (l1=='n')
                    a+=101101110;
                if (l1=='o')
                    a+=101101111;
                if (l1=='p')
                    a+=101110000;
                if (l1=='q')
                    a+=101110001;
                if (l1=='r')
                    a+=101110010;//a+=101110010;
                if (l1=='s')
                    a+=101110011;
                if (l1=='t')
                    a+=101110100;
                if (l1=='u')
                    a+=101110101;
                if (l1=='v')
                    a+=101110110;
                if (l1=='w')
                    a+=101110111;
                if (l1=='x')
                    a+=101111000;
                if (l1=='y')
                    a+=101111001;
                if (l1=='z')
                    a+=101111010;

    return a;
}

void convert(const char inp[], QString &tomatrix, int langht)
{
    unsigned long long a;
    int timarr[22],i=0;
    while (i<langht)
    {
        if (langht-i>=2)
        {
            a=char_to_aski(inp[i]);
            a=a*100000000;
            a+=char_to_aski(inp[i+1]);
            a=a-100000000;
        }
        if (langht-i<2)
            a=char_to_aski(inp[i])*100000000+100100000-100000000;
        for (int j=21; j>0; j--)//тут
        {
           if(j==1 || j==2 || j==4 || j==8 || j==16)
                timarr[j]=0;
            else
            {
                timarr[j]= a%10;
                a=a/10;
            }
       }
        if ((timarr[1]+timarr[3]+timarr[5]+timarr[7]+timarr[9]+timarr[11]+timarr[13]+timarr[15]+timarr[17]+timarr[19]+timarr[21])%2!=0)
            timarr[1]=1;
        if ((timarr[2]+timarr[3]+timarr[6]+timarr[7]+timarr[10]+timarr[11]+timarr[14]+timarr[15]+timarr[18]+timarr[19])%2!=0)
            timarr[2]=1;
        if ((timarr[4]+timarr[5]+timarr[6]+timarr[7]+timarr[12]+timarr[13]+timarr[14]+timarr[15]+timarr[20]+timarr[21])%2!=0)
            timarr[4]=1;
        if ((timarr[8]+timarr[9]+timarr[10]+timarr[11]+timarr[12]+timarr[13]+timarr[14]+timarr[15])%2!=0)
            timarr[8]=1;
        if ((timarr[16]+timarr[17]+timarr[18]+timarr[19]+timarr[20]+timarr[21])%2!=0)
            timarr[16]=1;
        for (int l=1; l<=21; l++)//тут
        tomatrix += (QString::number(timarr[l])+' ');
        tomatrix += '\n';
        if(langht-i>=2 || langht==1)
            i=i+2;
        else
            i+=1;
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    int height;
        input_info = ui->linin->text();
        height=std::size(input_info);
        QByteArray ba = input_info.toLocal8Bit();
        const char *input_strinfg = ba.data();
        convert(input_strinfg, output, height);
        QMessageBox::StandardButton react = QMessageBox::question(this, "matrix recording", output + "\n remember the resulting matrix?", QMessageBox::Yes | QMessageBox::No);
        if (react == QMessageBox::Yes)
        {
            input_info = "";
        }
        else
        {
            input_info = "";
            output ="";
        }
}


void MainWindow::on_pushButton_clicked()
{
    if (output!="")
           QMessageBox::information (this,"matrix recording", output);
       else
           QMessageBox::information (this,"matrix recording", "it's nosing here");
}


void MainWindow::on_pushButton_3_clicked()
{
    input_info = "";
    output ="";
}

void decodeing(std::string &ins,int lan)
{
    std::string vp1;
    std::string column1 = "101010101010101010101";
    std::string column2 = "011001100110011001100";
    std::string column3 = "000111100001111000011";
    std::string column4 = "000000011111111000000";
    std::string column5 = "000000000000000111111";
    long int k, ferst, sekond;
    int arr[6]={0},erpoint;
    int i=lan/21;
    for (int j=1; j<=i; j++)
    {
        erpoint=0;
        k=1; ferst=1; sekond=1;
        vp1 = ins.substr(0,21);
        ins.erase(0,21);
        for(int h=0; h<21; h++)
        {
            if (column1[h] == '1' && vp1[h] == '1')
                arr[1]++;
            if (column2[h] == '1' && vp1[h] == '1')
                arr[2]++;
            if (column3[h] == '1' && vp1[h] == '1')
                arr[3]++;
            if (column4[h] == '1' && vp1[h] == '1')
                arr[4]++;
            if (column5[h] == '1' && vp1[h] == '1')
                arr[5]++;
        }
        for (int h=1; h < 6; h++)
        {
            if (arr[h] % 2 == 1)
                erpoint+=pow(2,h-1);
        }
        qDebug() << erpoint;
        if (erpoint!=0)
        {
        if(vp1[erpoint-1] == '0')
            vp1[erpoint-1] = '1';
        else
            vp1[erpoint-1] = '0';
        }
        for (int y = 0; y < 21; y++)
        {
            if (vp1[y]=='0' && y<12 && y!=0 && y!=1 && y!=3 && y!=7 && y!= 15)
            {ferst=ferst*10; qDebug() << "ferst=" << ferst << " " << y;}
            else
            if (vp1[y]=='1' && y<12 && y!=0 && y!=1 && y!=3 && y!=7 && y!= 15)
                 {ferst=ferst*10+1; qDebug() << "ferst=" << ferst << " " << y;}
            else
            if (vp1[y]=='0' && y>11 && y!=0 && y!=1 && y!=3 && y!=7 && y!= 15)
            {sekond=sekond*10; qDebug() << "sekond=" << sekond << " " << y;}
            else
            if (vp1[y]=='1' && y>11 && y!=0 && y!=1 && y!=3 && y!=7 && y!= 15)
            {sekond=sekond*10+1; qDebug() << "sekond=" << sekond << " " << y;}
        }
        qDebug() << ferst << " " << sekond;
        askii_to_char(ferst);
        askii_to_char(sekond);
    }
}

void MainWindow::on_pushButton_4_clicked()
{
    outputd = "";
    int langh;
    decode = ui->mlinin->text();
    std::string input_strinfg = decode.toLocal8Bit().constData();
    langh=std::size(decode);
    decodeing(input_strinfg,langh);
    QMessageBox::information (this,"decode recording", outputd);
}

void MainWindow::on_pushButton_5_clicked()
{
    std::string inpiking="";
    outputd = "";
    int sz,count=0;
    if (output=="")
        QMessageBox::warning (this, "decode", "it's nothiong there");
    else
    {
        std::string input_strinfg = output.toLocal8Bit().constData();
        sz=std::size(input_strinfg);
        qDebug() << sz;
        for(int i=0; i<=sz; i++)
            if (input_strinfg[i]=='1' || input_strinfg[i]=='0')
            {
                inpiking += input_strinfg[i];
                count++;
            }
        sz=count;
        qDebug() << count;
        decodeing(inpiking,sz);
        QMessageBox::information (this,"decode recording", outputd);
    }
}

void MainWindow::on_pushButton_6_clicked()
{
    outputd="";
}

void MainWindow::on_pushButton_7_clicked()
{
    if (outputd=="")
        QMessageBox::warning (this,"decode line recording", "it's nosing here");
    else
        QMessageBox::information (this,"decode line", outputd);
}
