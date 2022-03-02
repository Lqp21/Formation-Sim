
%��������ϵ�µ���
T=zeros(data_num,6);%Force��bodyfixed
T(:,6)=45;

%%���ݼ�¼
V_record=[];%��������ٶȼ�¼
angle_record=[];%�Ƕȼ�¼
pos_record=[];%λ�ü�¼
pos_real_record=[];
acc_record=[];%���ٶȼ�¼
gyro_record=[];%���ٶ�
mag_record=[];%�ų�ǿ��
T_record=[];%���ļ�¼
M_record=[];%���صļ�¼
V_body_record=[];
SBL_record=[];%SBL����
SLAM_record=[];%�Ӿ�slam��ȡ��λ��
VO_record=[];%�Ӿ�slam��ȡ��λ��


%state
u=0;v=0;w=0;p=0;q=0;r=0;
Ve=[u v w p q r]';%linear velocity
angle=zeros(data_num,3);%eular angle

q=[1 0 0 0]';
%����ord45���Ӧ���Ǿ�����ߵ���
%���̬��Ӧ 

Cbn=zeros(3,3);
gmu=[0 0 0 0 0 0]';%����W=B=25kg������gmu

V_nav=[0 0 0]';
V_body=[0 0 0]';
Pos_nav=[0 0 0]';
pos_real_nav=[0 0 0]';

roll=0;pitch=0;yaw=0;
%��������
vector=[];

for j=1:data_num
    T_record(j,1)=T(j,1)';
    T_record(j,2)=T(j,2)';
    T_record(j,3)=T(j,3)';
    M_record(j,1)=T(j,4)';
    M_record(j,2)=T(j,5)';
    M_record(j,3)=T(j,6)'; 
    
    VNED_last=Cbn*Ve(1:3); %��õ�ǰ���ٶ�ʸ��
    
    v1=Ve(1:3);%���ٶ�
    v2=Ve(4:6);%���ٶ�
    
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
         
    %ŷ�����������ǿ�����
     gmu=[0,0,0,rgb*W*cos(pitch)*sin(roll),rgb*W*sin(pitch),0]';%����W=B=25kg������gmu
     Ve=Ve+invM*(T(j,:)'- Dr_quad*(abs(Ve).*(Ve))-Dr_linear*Ve-CV*Ve-gmu)*step;%����������ſ˱Ⱦ���      
     
    %���ݼ�¼�ĽǶȻ��ֻ�ýǶ�
    wx=Ve(4);%p
    wy=Ve(5);%q
    wz=Ve(6);%r
    %%��ȡ��Ԫ��΢��
    Q=[0,-wx/2,-wy/2,-wz/2;
        wx/2,0,wz/2,-wy/2;
        wy/2,-wz/2,0,wx/2;
        wz/2,wy/2,-wx/2,0];
    %%������̬��Ԫ��
    q=q+Q*q*step;
    %��Ԫ��תŷ����
     [yaw,pitch,roll]=quat2angle(q');
     %����
     qsum=norm(q);
     q(1)=q(1)/qsum;
     q(2)=q(2)/qsum;
     q(3)=q(3)/qsum;
     q(4)=q(4)/qsum;

    %% ��¼��ֵ���ݣ���������ϵΪ������   
     angle_real_record(j,1)=roll*57.3;
     angle_real_record(j,2)=pitch*57.3;
     angle_real_record(j,3)=yaw*57.3;


    %������̬��ת����ע�������������ǳ��ؼ���
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
    %ע����ٶȼƲ������ǹ��Կռ��еļ��ٶ�
    VNED_now=Cbn*Ve(1:3); %��õ�ǰ���ٶ�ʸ��
    acc_Tem=Cnb*(VNED_now-VNED_last)/step;%��ü��ٶȼƵĲ���ֵ    
    gravity_g=[0 0 -g]';%%ned�м��ٶȳ��ϣ���Ϊ��
    gravity_projection=Cnb*gravity_g;%����ͶӰ��������ϵ��

     if mod((j-1)*step,1/IMU_update_rate)==0  
              %%body fixed acc
          acc_record(j,1)=acc_Tem(1)+gravity_projection(1);
          acc_record(j,2)=acc_Tem(2)+gravity_projection(2);
          acc_record(j,3)=acc_Tem(3)+gravity_projection(3); 
          gyro_record(j,:)=[wx wy wz];%rad
     else
          acc_record(j,:)=acc_record(j-1,:);%������һʱ�̵�ֵ
          gyro_record(j,:)=gyro_record(j-1,:);
     end
     
    %%��������ų�
     if mod((j-1)*step,1/MAG_update_rate)==0  
         
     mag=[30000 0 -40000]';%����ų�ǿ����y��û��ͶӰ����û�д�ƫ��
     mag_projection=Cnb*mag;    
     mag_record(j,:)=mag_projection';
     else
           mag_record(j,:)=mag_record(j-1,:);
     end

     %%��������λ����Ϣ
      pos_real_nav=pos_real_nav+Cbn*Ve(1:3)*step;
      pos_real_record(j,:)=pos_real_nav;
      
     if mod((j-1)*step,1/SBL_update_rate)==0
          SBL_Length=sqrt(pos_real_record(j,1)*pos_real_record(j,1)+pos_real_record(j,2)*pos_real_record(j,2));   
          SBL_noise=(SBL_Length/25).*randn(1,2);   %25�����������ص����ϵ��

          SBL_record(j,:)=pos_real_record(j,:);
          SBL_record(j,1:2)=SBL_record(j,1:2);%SBL����   
     else
          SBL_record(j,:)=SBL_record(j-1,:);%������һʱ�̵�ֵ
     end
          SBL_record(j,3)=SBL_record(j,3);%SBL����  
          
      if mod((j-1)*step,1/SLAM_update_rate)==0
          SLAM_record(j,:)=pos_real_record(j,1:2);
     else
          SLAM_record(j,:)=SLAM_record(j-1,:);%������һʱ�̵�ֵ
      end
      
     if mod((j-1)*step,1/VO_update_rate)==0
          VO_record(j,:)=Ve;
          
     else
          VO_record(j,:)=VO_record(j-1,:);%������һʱ�̵�ֵ
     end
     V_body_real_record(j,:)=Ve;%%������ٶ���ֵ
     fprintf('simu_num=%d/%d\r\n',j,data_num);
end    