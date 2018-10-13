fileMA1 = fopen('../resultados/moving1.csv');
fileMA2 = fopen('../resultados/moving2.csv');



if fileMA1 >0
    data = textscan(fileMA1, '%s %f', 'Delimiter', ',');
    data2= textscan(fileMA2, '%s %f', 'Delimiter', ',');
    
    fclose(fileMA1);
end

x = data{:,1};
y = data{:,2};
y2 = data2{:,2};

x = datenum(data{:,1}, 'yyyy/mm/dd');

plot(x,y, 'b'); hold on;
plot(x,y2, 'r');

datetick('x','yyyy/mm/dd','keepticks');