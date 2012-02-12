function [ sample ] = datalogger( bee,adc_chan,n_sample,time_delay )

%BeeBoard & Matlab, simple example datalogger
%  input:
%           "bee"        : arduino object
%           "adc_cahn"   : number of ADC channel
%           "n_sample"   : number of capture Sample
%           "time_delay" : acquisition interval in sec

sample=[];

for i=1:n_sample,
    sample(i)=bee.analogRead(adc_chan);
    
    
    subplot(3,1,1); plot(sample);  % add raw Sample plot
    title('ADC raw Sample');
    
    subplot(3,1,2); plot(sample*(3.3/1024));  % add ADC voltage plot 
    title('ADC voltage Sample');
    
    subplot(3,1,3); plot(abs(fft(sample))); % add FFT sample
    title('FFT ADC value');
    
    pause(time_delay);
    
end

end

