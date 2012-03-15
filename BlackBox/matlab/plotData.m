close all
clear all

importCSV('/Users/danielesdei/Desktop/DUMP.CSV')

nsamples = length(data);
step = 0.2;
t = (0:step:step*(nsamples-1));  % seconds

lat = data(:,3);
lon = data(:,4);
course = data(:,5);
speed = data(:,6);
alt = data(:,7);
magnX = data(:,8);
magnY = data(:,9);
magnZ = data(:,10);
accX = data(:,11);
accY = data(:,12);
accZ = data(:,13);
gyroX = data(:,14);
gyroY = data(:,15);
gyroZ = data(:,16);
baroTemp = data(:,17);
baroPres = data(:,18);
baroAlt = data(:,19);

figure
latlim = [min(lat)-0.001 max(lat)+0.001];
lonlim = [min(lon)-0.001 max(lon)+0.001];
worldmap(latlim,lonlim)
plotm(lat,lon)
title('Tour Map')

figure
plot(t,course)
title('GPS Course')
xlabel('Time [s]')

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