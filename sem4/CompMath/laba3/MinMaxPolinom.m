function retval = MinMaxPolinom (input1)
del=input1(1);

for(i =length(input1):-1:1)
input1(i)=input1(i)/del;
input2=input1;
if(rem(i,2)==1)
input2(i)=-input1(i);
end;

end;
max=-1;
min=1;
firstplus=-1;
firstminus=-1;
for(i=1:1:length(input1))
if(input2(i)>0&&input2(i)>max)
max=input2(i);
end;
if(input1(i)<0&&input1(i)<min)
min=input1(i);
end;
if(input2(i)>0&&firstplus==-1)
firstplus=i-1;
end;
if(input1(i)<0&&firstminus==-1)
firstminus=i-1;
end
end

maxkor=1+abs(min)**(1/firstminus);
minkor=-(1+abs(max)**(1/firstplus));
retval = [minkor,maxkor];
endfunction