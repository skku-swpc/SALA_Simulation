% Draw Room's Shape
room = fopen('./room.txt', 'r');
fscanf(room, '%g', 1);
w=fscanf(room, '%d', 1);
h=fscanf(room, '%d', 1);
start = fscanf(room, '%g', 2);
nWall = fscanf(room, '%d', 1);
i=0;
while i<nWall;
    i=i+1;
    wall = fscanf(room, '%g', [2 2]);
    plot(wall(1, :), wall(2, :), 'black', 'LineWidth', 2);
    hold on;
end;
nDoor = fscanf(room, '%d', 1);
i=0;
t=0:0.01:pi/4+0.01;


while i<nDoor;
    i=i+1;
    door = fscanf(room, '%g', [2 2]);
    plot(door(1, :), door(2, :), 'white', 'LineWidth', 2);
    hold on;
    a=door(1, 1);
    c=door(1, 2);
    b=door(2, 1);
    d=door(2, 2);
    if door(2, 1)==door(2, 2);
        plot(a+(c-a)*cos(t), b+(c-a)*sin(t), 'black');
        x = [a a+(c-a)*cos(pi/4)];
        y = [b b+(c-a)*sin(pi/4)];
    else
        plot(a+(d-b)*sin(t), b+(d-b)*cos(t), 'black');
        x = [a a+(d-b)*sin(pi/4)];
        y = [b b+(d-b)*cos(pi/4)];
    end;
    hold on;
    plot(x, y, 'black');
    hold on;
end;
axis('equal');
axis([0 w 0 h]);
fclose(room);


% 상수로 입력해줄 부분
cases = 1;
iaNum = 10;

is_circ=0;
is_medi=0;
is_matl=1;
is_chos=0;
is_conv=0;
is_long=0;
is_real=0;
is_resu=0;
% End

N = 2+iaNum;

circ = fopen(strcat('./out/',num2str(cases),'circum.txt'),'r');
medi = fopen(strcat('./out/',num2str(cases),'median.txt'),'r');
matl = fopen('./data/MATlist120.txt','r');
chos = fopen(strcat('./out/',num2str(cases),'chosen.txt'),'r');
conv = fopen(strcat('./out/',num2str(cases),'convex.txt'),'r');
long = fopen(strcat('./out/',num2str(cases),'long.txt'),'r');
resu = fopen(strcat('./out/',num2str(cases),'result.txt'),'r');
reap = fopen(strcat('./out/',num2str(cases),'real.txt'),'r');

%text(15, 980, strcat('case ',num2str(cases)), 'Color', 'k');

i=2; 
while i<N && is_circ;
    m = fscanf (circ, '%d',1);
    j=0;
    while j<m;
        real = fscanf (circ, '%g', [1 2]);
        x = real(1, 1);
        y = real(1, 2);
        plot (x,y,'g*');
        j=j+1;
    end;
    i=i+1;
end;

test_case = 2

%--------------------------------------------------------------------------
% get appliance real location
loc = fopen('./data/location1.txt', 'r');
i=2;
location = [0,0];
while i<N;
    ia = fscanf (loc, '%d',1);
    real = fscanf (loc, '%g', [1 2]);
    x = real(1, 1);
    y = real(1, 2);
    if 1%i == test_case
        plot (x,y, '*', 'Color', 'blue');
        s=[num2str(ia-1)];% ' : (' num2str(x) ', ' num2str(y) ')'];
        text(x+10, y, s, 'Color', 'blue');
    end
    location=[location;real];
    i=i+1;
end;
fclose (loc);

%--------------------------------------------------------------------------
% get appliance real location
loc = fopen('./out/result.txt', 'r');

% for i = 1:3
%     for j = 2:11
%         real = fscanf (loc, '%g', [1 2]);
%         x = real(1, 1);
%         y = real(1, 2);
%         if 1%j == test_case
%             plot (x,y, '*', 'Color', 'black');
%             if i == 1
%                 text(x+3, y, 'Convex', 'Color', 'black');
%             elseif i == 2
%                 text(x+3, y, 'RSSI', 'Color', 'black');
%             else
%                 text(x+3, y, 'SALA', 'Color', 'black');
%             end
%         end
%     end
% end
% fclose (loc);

if is_matl
    %m = fscanf (matl, '%d',1);
    j=0;
    while true
        i = fscanf (matl, '%d', 1);
        real = fscanf (matl, '%g', [1 3]);
        power = real(1, 1);
        x = real(1, 2);
        y = real(1, 3);
        %if i==2 || i==6 || i==7 || i==8
        %    plot (x,y,'c*');
        %else
        %    plot (x,y,'g*');
        %end;
        
        if 1%i == test_case
            if power <= 0.000000050
                plot (x,y, '.', 'color', [200 200 200]/255);
            elseif power <= 0.000000400
                plot (x,y, '.', 'color', [200 200 200]/255);
                %plot (x,y, '.', 'color', [0 0 255]/255);
            elseif power <= 0.000000800
                %plot (x,y, '.', 'color', [200 200 200]/255);
                plot (x,y, '.', 'color', [0 255 0]/255);
            else
                %plot (x,y, '.', 'color', [0 0 0]/255);
                plot (x,y, '.', 'color', [255 0 0]/255);
            end
        end
        
        j=j+1;
    end
end

i=2;
while i<N && is_chos;
    m = fscanf (chos, '%d',1);
    j=0;
    while j<m;
        real = fscanf (chos, '%g', [1 2]);
        x = real(1, 1);
        y = real(1, 2);
            plot (x,y,'g*');
        j=j+1;
    end;
    i=i+1;
end;

i=2;
while i<N && is_conv;
    m = fscanf (conv, '%d',1);
    j=0;
    realdata = [0,0];
    while j<m;
        real = fscanf (conv, '%g', [1 2]);
        x1=x, x = real(1, 1);
        y1=y, y = real(1, 2);
       
        plot (x,y,'g*');
        
        if (j==0)
            x0=x, y0=y;
        end;
        if (j>0)
            plot ([x1 x], [y1 y], 'g');
            x1=x, y1=y;
        end;        
        j=j+1;
        
        if j==m
            plot ([x0 x], [y0 y], 'g');
        end;
    end;
    i=i+1;
end;

i=2;
while i<N && is_medi;
    i=i+1;
    ia = fscanf (medi, '%d',1);
    real = fscanf (medi, '%g', [1 2]);
    
    x = real(1, 1);
    y = real(1, 2);
	plot (x,y, 'r*');
    s=[num2str(ia)];% ' : (' num2str(x) ', ' num2str(y) ')'];
end;


i=2;
while i<N && is_long;
    ia = fscanf (long, '%d',1);
    real = fscanf (long, '%g', [1 2]);
    
    p1 = fscanf (long, '%g',[1 2]); 
    p2 = fscanf (long, '%g',[1 2]); 
    
    if i>1
        plot (p1(1,1),p1(1,2),'m*'); %text(p1(1,1)+10,p1(1,2), num2str(ia), 'Color', 'm');
        plot (p2(1,1),p2(1,2),'m*'); %text(p2(1,1)+10,p2(1,2), num2str(ia), 'Color', 'm');
        plot ([p1(1,1) p2(1,1)], [p1(1,2), p2(1,2)], 'k');
    end;
    
    x = real(1, 1);
    y = real(1, 2);
% 	plot (x,y, 'r*');
    s=[num2str(ia)];;
%     text(x+10, y, s, 'Color', 'r');
    i=i+1;
end;

i=2;
while i<N && is_resu;
    i=i+1;
    ia = fscanf (resu, '%d',1);
    real = fscanf (resu, '%g', [1 2]);
    
    x = real(1, 1);
    y = real(1, 2);
	plot (x,y, 'r*');
    text(x+10, y, num2str(ia), 'Color', 'red');
end;

i=2;
while i<N && is_real;
    ia = fscanf (reap, '%d',1);
    real = fscanf (reap, '%g', [1 2]);
    
    p1 = fscanf (reap, '%g',[1 2]); 
    p2 = fscanf (reap, '%g',[1 2]); 
    
    if i>1
        plot (p1(1,1),p1(1,2),'r*');
        text(x+10, y, s, 'Color', 'r');
        %plot (p2(1,1),p2(1,2),'r*');
    end;
    
    x = real(1, 1);
    y = real(1, 2);
	plot (x,y, 'k*');
    i=i+1;
end;

fig1 = figure(1);
set(fig1, 'OuterPosition', [220, 170, 640, 720])