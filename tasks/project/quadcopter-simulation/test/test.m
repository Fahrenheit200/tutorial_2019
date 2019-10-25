function test
clear all
clc

global A

% ͼ��
figure('units','normalized','position',[.1 .1 .8 .8],'name','Quadrotor','color','w');
axes('units','normalized','position',[.2 .1 .6 .8]);
axis equal    

% ��ʼ�����������Լ�����ģ��
All_Variables;
quadmodel;

%GUI
% Altitude          -- E1
% Roll              -- E2
% Pitch             -- E3
% Yaw               -- E4
% X                 -- E5
% Y                 -- E6
E1 = uicontrol('units','normalized','position',[.11 .85 .1 .07],'style','edit','fontsize',13,'string',0,'backgroundcolor','w');
E2 = uicontrol('units','normalized','position',[.11 .75 .1 .07],'style','edit','fontsize',13,'string',0,'backgroundcolor','w');
E3 = uicontrol('units','normalized','position',[.11 .65 .1 .07],'style','edit','fontsize',13,'string',0,'backgroundcolor','w');
E4 = uicontrol('units','normalized','position',[.11 .55 .1 .07],'style','edit','fontsize',13,'string',0,'backgroundcolor','w');
E5 = uicontrol('units','normalized','position',[.11 .45 .1 .07],'style','edit','fontsize',13,'string',0,'backgroundcolor','w');
E6 = uicontrol('units','normalized','position',[.11 .35 .1 .07],'style','edit','fontsize',13,'string',0,'backgroundcolor','w');

uicontrol('units','normalized','position',[.02 .83 .05 .07],'style','text','fontsize',13,'string','Altitude','backgroundcolor','w');
uicontrol('units','normalized','position',[.02 .73 .05 .07],'style','text','fontsize',13,'string','Roll','backgroundcolor','w');
uicontrol('units','normalized','position',[.02 .63 .05 .07],'style','text','fontsize',13,'string','Pitch','backgroundcolor','w');
uicontrol('units','normalized','position',[.02 .53 .05 .07],'style','text','fontsize',13,'string','Yaw','backgroundcolor','w');
uicontrol('units','normalized','position',[.02 .43 .05 .07],'style','text','fontsize',13,'string','X','backgroundcolor','w');
uicontrol('units','normalized','position',[.02 .33 .05 .07],'style','text','fontsize',13,'string','Y','backgroundcolor','w');

% Go��ť
uicontrol('units','normalized','position',[.11 .25 .1 .07],'style','pushbutton','fontsize',13,'string','Go','callback',@Go);

% ��ʾ�����ٶ�
uicontrol('units','normalized','position',[.85 .83 .05 .07],'style','text','fontsize',13,'string','Front M','backgroundcolor',[.5 .7 1]);
uicontrol('units','normalized','position',[.85 .73 .05 .07],'style','text','fontsize',13,'string','Right M','backgroundcolor',[.5 .7 1]);
uicontrol('units','normalized','position',[.85 .63 .05 .07],'style','text','fontsize',13,'string','Rear M','backgroundcolor',[.5 .7 1]);
uicontrol('units','normalized','position',[.85 .53 .05 .07],'style','text','fontsize',13,'string','Left M','backgroundcolor',[.5 .7 1]);

O1 = uicontrol('units','normalized','position',[.91 .86 .08 .05],'style','text','fontsize',13,'string','0','backgroundcolor','w');
O2 = uicontrol('units','normalized','position',[.91 .76 .08 .05],'style','text','fontsize',13,'string','0','backgroundcolor','w');
O3 = uicontrol('units','normalized','position',[.91 .66 .08 .05],'style','text','fontsize',13,'string','0','backgroundcolor','w');
O4 = uicontrol('units','normalized','position',[.91 .56 .08 .05],'style','text','fontsize',13,'string','0','backgroundcolor','w');

% 3D����
axis([-50 50 -50 50 -2 50])
grid on
hold on

% ���
camproj perspective 
camva(25)

% ����ʼ��ʮ�ּ�
line([-.5 .5],[0 0],[0 0])
line([0 0],[-.5 .5],[0 0],'color','r')

%����ѭ����ʼ
while 1
tic;  
% ������ǰλ�˲���
   Z_meas;
   XY_meas;
   IMU_meas;
   
% ����PID������      
  % PID_X;
  % PID_Y;
   PID_Z;
   PID_roll;
   PID_pitch;
   PID_heading;

% ����ת�ٺ���  
   Motors_Speed;
   Forces;
   
% Ӧ���˶�����
   quadmodel;  

% չʾ�ĸ������ת��
   set(O1,'string',num2str(A.O1));
   set(O2,'string',num2str(A.O2));
   set(O3,'string',num2str(A.O3));
   set(O4,'string',num2str(A.O4));
   
% ���·ɻ���λ��     
   plot_quad_3D;  
      
% �������
   campos([A.X+2 A.Y+2 A.Z+2])
   camtarget([A.X A.Y A.Z])
      
% ʵʱ����
   drawnow
   toc
   
   A.init = 1;  % ����ѭ��
end

% �Ӻ��� Go
% Altitude          -- E1
% Roll              -- E2
% Pitch             -- E3
% Yaw               -- E4
% X                 -- E5
% Y                 -- E6
    function Go(varargin)
        A.Z_des = str2double(get(E1,'string'));
        A.phi_des = str2double(get(E2,'string'))*pi/180;
        A.theta_des = str2double(get(E3,'string'))*pi/180;
        A.psi_des = str2double(get(E4,'string'))*pi/180;
        A.X_des_EF = str2double(get(E5,'string'));
        A.Y_des_EF = str2double(get(E6,'string'));
    end
end