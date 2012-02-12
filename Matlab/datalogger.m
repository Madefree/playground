function [ sample ] = datalogger( bee,n_sample,time_delay )

%BeeBoard & Matlab, simple example datalogger
%  input:
%           "bee"        : arduino object
%           "n_sample"   : number of capture Sample
%           "time_delay" : acquisition interval in sec

sample=[];

for i=1:n_sample,
    
    sample(1,i)=bee.analogRead(0);
    sample(2,i)=bee.analogRead(1);
    sample(3,i)=bee.analogRead(2);
    sample(4,i)=bee.analogRead(3);
    
    % Add raw Sample plot
    x=[1:i];
    y1=sample(1,:);
    y2=sample(2,:);
    y3=sample(3,:);
    y4=sample(4,:);
    
    subplot(2,1,1); plot(x,y1,x,y2,x,y3,x,y4);
    title('ADC raw Sample');
    legend('chan0','chan1','chan2','chan3');
    
    % add ADC voltage plot 
    y1=sample(1,:)*(3.3/1024);
    y2=sample(2,:)*(3.3/1024);
    y3=sample(3,:)*(3.3/1024);
    y4=sample(4,:)*(3.3/1024);
    
    subplot(2,1,2); plot(x,y1,x,y2,x,y3,x,y4);
    title('ADC voltage Sample');
    legend('chan0','chan1','chan2','chan3');
    
    pause(time_delay);
    
end
end

