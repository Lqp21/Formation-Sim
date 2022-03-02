
%载体坐标系下的力
T=zeros(data_num,6);%Force，bodyfixed
T(:,6)=45;

%%数据记录
V_record=[];%载体固连速度记录
angle_record=[];%角度记录
pos_record=[];%位置记录
pos_real_record=[];
acc_record=[];%加速度记录
gyro_record=[];%角速度
mag_record=[];%磁场强度
T_record=[];%力的记录
M_record=[];%力矩的记录
V_body_record=[];
SBL_record=[];%SBL数据
SLAM_record=[];%视觉slam获取的位置
VO_record=[];%视觉slam获取的位置


%state
u=0;v=0;w=0;p=0;q=0;r=0;
Ve=[u v w p q r]';%linear velocity
angle=zeros(data_num,3);%eular angle

q=[1 0 0 0]';
%采用ord45这个应该是精度最高的了
%零初态响应 

Cbn=zeros(3,3);
gmu=[0 0 0 0 0 0]';%假设W=B=25kg，跟新gmu

V_nav=[0 0 0]';
V_body=[0 0 0]';
Pos_nav=[0 0 0]';
pos_real_nav=[0 0 0]';

roll=0;pitch=0;yaw=0;
%方向向量
vector=[];

for j=1:data_num
    T_record(j,1)=T(j,1)';
    T_record(j,2)=T(j,2)';
    T_record(j,3)=T(j,3)';
    M_record(j,1)=T(j,4)';
    M_record(j,2)=T(j,5)';
    M_record(j,3)=T(j,6)'; 
    
    VNED_last=Cbn*Ve(1:3); %获得当前的速度矢量
    
    v1=Ve(1:3);%线速度
    v2=Ve(4:6);%角速度
    
    M11=[M(1,1) M(1,2) M(1,3)
         M(1,1) M(1,2) M(1,3)
         M(1,1) M(1,2) M(1,3)];
     
    M12=[M(1,4) M(1,5) M(1,6)
         M(2,4) M(2,5) M(2,6)
         M(3,4) M(3,5) M(3,6)];
     
    M21=[M(4,1) M(4,2) M(4,3)
         M(5,1) M(5,2) M(5,3)
         M(6,1) M(6,2) M(6,3)];
     
    M22=[M(4,4) M(4,5) M(4,6)
         M(5,4) M(5,5) M(5,6)
         M(6,4) M(6,5) M(6,6)];
    o33=zeros(3,3);    
    CV=[o33                   -my_smtrx(M11*v1+M12*v2)
        -my_smtrx(M11*v1+M12*v2) -my_smtrx(M21*v1+M22*v2)];
         
    %欧拉法，不考虑科氏力
     gmu=[0,0,0,rgb*W*cos(pitch)*sin(roll),rgb*W*sin(pitch),0]';%假设W=B=25kg，跟新gmu
     Ve=Ve+invM*(T(j,:)'- Dr_quad*(abs(Ve).*(Ve))-Dr_linear*Ve-CV*Ve-gmu)*step;%多变量求导是雅克比矩阵      
     
    %根据记录的角度积分获得角度
    wx=Ve(4);%p
    wy=Ve(5);%q
    wz=Ve(6);%r
    %%获取四元数微分
    Q=[0,-wx/2,-wy/2,-wz/2;
        wx/2,0,wz/2,-wy/2;
        wy/2,-wz/2,0,wx/2;
        wz/2,wy/2,-wx/2,0];
    %%更新姿态四元数
    q=q+Q*q*step;
    %四元数转欧拉角
     [yaw,pitch,roll]=quat2angle(q');
     %范化
     qsum=norm(q);
     q(1)=q(1)/qsum;
     q(2)=q(2)/qsum;
     q(3)=q(3)/qsum;
     q(4)=q(4)/qsum;

    %% 记录真值数据，地理坐标系为北东地   
     angle_real_record(j,1)=roll*57.3;
     angle_real_record(j,2)=pitch*57.3;
     angle_real_record(j,3)=yaw*57.3;


    %更新姿态旋转矩阵，注意这个放在哪里非常关键。
    Cbn(1,1)=q(1)^2+q(2)^2-q(3)^2-q(4)^2;
    Cbn(1,2)=2*(q(2)*q(3)-q(1)*q(4)); 
    Cbn(1,3)=2*(q(1)*q(3)+q(2)*q(4)); 
    Cbn(2,1)=2*(q(2)*q(3)+q(1)*q(4));
    Cbn(2,2)=q(1)^2-q(2)^2+q(3)^2-q(4)^2;
    Cbn(2,3)=2*(q(3)*q(4)-q(1)*q(2));
    Cbn(3,1)=2*(-q(1)*q(3)+q(2)*q(4));
    Cbn(3,2)=2*(q(3)*q(4)+q(1)*q(2));
    Cbn(3,3)=q(1)^2-q(2)^2-q(3)^2+q(4)^2;
    Cnb=Cbn';
    
    unit=[1 0 0]';
    vector(j,:)=(Cbn*unit)';
    %注意加速度计测量的是惯性空间中的加速度
    VNED_now=Cbn*Ve(1:3); %获得当前的速度矢量
    acc_Tem=Cnb*(VNED_now-VNED_last)/step;%获得加速度计的测量值    
    gravity_g=[0 0 -g]';%%ned中加速度朝上，则为负
    gravity_projection=Cnb*gravity_g;%重力投影到体坐标系下

     if mod((j-1)*step,1/IMU_update_rate)==0  
              %%body fixed acc
          acc_record(j,1)=acc_Tem(1)+gravity_projection(1);
          acc_record(j,2)=acc_Tem(2)+gravity_projection(2);
          acc_record(j,3)=acc_Tem(3)+gravity_projection(3); 
          gyro_record(j,:)=[wx wy wz];%rad
     else
          acc_record(j,:)=acc_record(j-1,:);%等于上一时刻的值
          gyro_record(j,:)=gyro_record(j-1,:);
     end
     
    %%生成虚拟磁场
     if mod((j-1)*step,1/MAG_update_rate)==0  
         
     mag=[30000 0 -40000]';%假设磁场强度在y轴没有投影，即没有磁偏角
     mag_projection=Cnb*mag;    
     mag_record(j,:)=mag_projection';
     else
           mag_record(j,:)=mag_record(j-1,:);
     end

     %%生成虚拟位置信息
      pos_real_nav=pos_real_nav+Cbn*Ve(1:3)*step;
      pos_real_record(j,:)=pos_real_nav;
      
     if mod((j-1)*step,1/SBL_update_rate)==0
          SBL_Length=sqrt(pos_real_record(j,1)*pos_real_record(j,1)+pos_real_record(j,2)*pos_real_record(j,2));   
          SBL_noise=(SBL_Length/25).*randn(1,2);   %25代表跟距离相关的误差系数

          SBL_record(j,:)=pos_real_record(j,:);
          SBL_record(j,1:2)=SBL_record(j,1:2);%SBL数据   
     else
          SBL_record(j,:)=SBL_record(j-1,:);%等于上一时刻的值
     end
          SBL_record(j,3)=SBL_record(j,3);%SBL数据  
          
      if mod((j-1)*step,1/SLAM_update_rate)==0
          SLAM_record(j,:)=pos_real_record(j,1:2);
     else
          SLAM_record(j,:)=SLAM_record(j-1,:);%等于上一时刻的值
      end
      
     if mod((j-1)*step,1/VO_update_rate)==0
          VO_record(j,:)=Ve;
          
     else
          VO_record(j,:)=VO_record(j-1,:);%等于上一时刻的值
     end
     V_body_real_record(j,:)=Ve;%%载体加速度真值
     fprintf('simu_num=%d/%d\r\n',j,data_num);
end    