close all
clear all

importCSV('/Users/danielesdei/Desktop/DUMP.CSV')

nsamples = length(data);
step = 0.2;
t = (0:step:step*(nsamples-1));  % seconds

time = data(:,1);
lat = data(:,2);
lon = data(:,3);
course = data(:,4);
speed = data(:,5);
alt = data(:,6);
magnX = data(:,7);
magnY = data(:,8);
magnZ = data(:,9);
accX = data(:,10);
accY = data(:,11);
accZ = data(:,12);
gyroX = data(:,13);
gyroY = data(:,14);
gyroZ = data(:,15);
baroTemp = data(:,16);
baroPres = data(:,17);
baroAlt = data(:,18);

figure
latlim = [min(lat)-0.001 max(lat)+0.001];
lonlim = [min(lon)-0.001 max(lon)+0.001];
worldmap(latlim,lonlim)
plotm(lat,lon)
title('Tour Map')

figure
plot(t,speed)
title('GPS Speed')
xlabel('Time [s]')
ylabel('Speed [km/h]')

figure
plot(t,alt,'b',t,baroAlt,'r')
title('GPS vs Baro Altitude')
xlabel('Time [s]')
ylabel('Altitude [m MSL]')
legend('GPS','Baro')

figure
plot(t,magnX,'g',t,magnY,'m',t,magnZ,'c')
title('Magnetometer Raw value')
xlabel('Time [s]')
legend('X Axis','Y Axis','Z Axis')

figure
plot(t,accX,'g',t,accY,'m',t,accZ,'c')
title('Accelerometer Raw value')
xlabel('Time [s]')
legend('X Axis','Y Axis','Z Axis')

figure
plot(t,gyroX,'g',t,gyroY,'m',t,gyroZ,'c')
title('Gyroscope Raw value')
xlabel('Time [s]')
legend('X Axis','Y Axis','Z Axis')

figure
plot(t,baroTemp)
title('Barometer Temperature')
xlabel('Time [s]')
ylabel('Temperature [°C]')

figure
plot(t,baroPres)
title('Barometer Pressure')
xlabel('Time [s]')
ylabel('Pressure [mbar]')