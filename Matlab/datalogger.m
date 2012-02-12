function [ sample ] = datalogger( bee,adc_chan,n_sample,time_delay )
%UNTITLED3 Summary of this function goes here
%   Detailed explanation goes here
sample=[];

for i=1:n_sample,
    sample(i)=bee.analogRead(adc_chan);
    
    
    subplot(3,1,1); plot(sample);
    title('ADC raw Sample');
    
    subplot(3,1,2); plot(sample);
    title('ADC voltage Sample');
    
    subplot(3,1,3); plot(abs(fft(sample)));
    title('FFT ADC value');
    
    pause(time_delay);
    
end

end

