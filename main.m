clc;
close all;

s1 = serial('/dev/ttyUSB0');    % define serial port
s1.BaudRate = 9600;               % define baud rate
set(s1, 'terminator', 'LF');    % define the terminator for println
fopen(s1);

var = 1;

engine = zeros(100,1);
gear = zeros(100,1);
seat = zeros(100,1);
brk = zeros(100,1);
fuel = zeros(100,1);
speed = zeros(100,1);

try
    while (1)
        [tline, count, msg] = fgetl(s1);
        disp(tline);
        if(count>3)
            engine(var) = str2num(tline(1));
            gear(var) = str2num(tline(2));
            seat(var) = str2num(tline(3));
            brk(var) = str2num(tline(4));
            fuel(var) = str2num(tline(5));
            speed(var) = str2num(tline(9:-1:6));
            disp (speed);
            var = var + 1;
            if(var>100)
                var = 1;
            end
        end
        figure(1), subplot(3,2,1), plot(speed,'LineWidth',2); axis([0, 100, 0, 1100]); grid on; title('Speed of the Car');
        subplot(3,2,2), plot(gear,'LineWidth',2,'Color','g'); axis([0, 100, -1, 6]);title('Gear of the Car');
        subplot(3,2,3), plot(seat,'LineWidth',2,'Color','y'); axis([0, 100, -1, 2]);title('Seat Belt Status');
        subplot(3,2,4), plot(brk,'LineWidth',2,'Color','r'); axis([0, 100, -1, 2]);title('Brake Status');
        subplot(3,2,5), plot(fuel,'LineWidth',2,'Color','k'); axis([0, 100, -1, 2]);title('Door Lock Status');
%         figure(2), plot(speed, 'Color', 'r'), hold on;
%         plot(gear*200, 'Color', 'b'), hold on;
%         plot(seat*500, 'Color', 'k'), hold on;
%         plot(brk*800, 'Color', 'y'), hold on; 
%         plot(100+fuel*250, 'Color', 'g');
    end
catch 
    fclose(s1);
    disp('here');
end


%instrfind
