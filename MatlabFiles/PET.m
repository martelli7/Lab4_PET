clear;
%----------------------------------------------
%Plotting the lines on a plate of radius R=186 mm
%For the many material:  a2 is the matrix with m and q values of the lines
% and their statistical errors 
%----a2 AIR-------------------------------------
%a2=[-30 89.5450000000000 3.85422276900000 0.0855600000000000 191.687000000000 1.96366000000000;0 136.300000000000 0.955620757000000 0.0103240000000000 0 1.21237100000000;-22.5000000000000 103.570000000000 2.16221578100000 0.0306080000000000 86.4447000000000 1.27151600000000;30 182.100000000000 0.229030574000000 0.00577400000000000 -49.3868000000000 0.924910000000000;15 159.600000000000 0.529472745000000 0.00676200000000000 -27.4709000000000 1.05309200000000];
%----a2 H2O--------------------------------------
a2=[0  136.9500    0.9340    0.0100         0    1.1990; -22.5000  107.8000    1.8000    0.0230   74.7300    1.2030; 30.0000  193.6000    0.0240    0.0060  -48.1500    0.8550; -30.0000   89.5450    3.8540    0.0860  191.6900    2.0280; 15.0000  169.5500    0.3240    0.0060  -25.5200    0.9530];
%---a2 NaCl--------------------------------------
%a2=[  0  145.7000    0.6820    0.0080         0    1.0610; -22.5000  108.8000    1.7290    0.0230   72.4600    1.2050; 30.0000   94.3950   -5.3410    0.1710  261.5800    5.0850; -30.0000   89.5450    3.8540    0.0990  191.6900    3.0250;];
%-----------------------------------------------------
%Creation of 5 matrix 372x372 (1 for each measure) full of zeros.

for i=1:5
s.a(i).b=zeros(372);
end
coefficienti=0;
%-----------------------------------------------------
%a1 = matrix 5x2 
% column 1 spectrometer angles, column 2 measured angles
%----a1 AIR-------------------------------------
a1=[-30 88; -22.5 103.57; 0 136.3; 15 159.6; 30 182.1];
%----a1 H2O-------------------------------------
%a1=[0 136.95; -22.5 107.8; 30 193.6; -30 89.545; 15 169.55]; 
%----a1 NaCL-------------------------------------
%a1= [0 145.70;-22.5 108.80;30 94.40; -30 89.55];
%-----------------------------------------------------

tan_theta = 12.7/(186+25.4); % sigma m sist
DeltaQ = 186*tan_theta; % sigma q sist
%Creation matrix for each measure
for n=2:5 %---AIR MEASUREMENTS
%for n=1:5 %---H2O MEASUREMENTS
%for n=1:4 %---NaCl MEASUREMENTS 

    p0=[-186 0]; %Coordinates Riv0
    p1=[186*cos(a1(n,1)*pi/180) 186*sin(a1(n,1)*pi/180)]; %Coordinates Riv1
    t=-a1(n,2)*pi/180; %Detectors' rotation angles
    u=[cos(t) -sin(t); sin(t) cos(t)]; %Rotation Matrix

    p00=u*p0'; %Coordinates Riv0 rotated
    p01=u*p1'; %Coordinates Riv1  rotated
    m=(p01(2)-p00(2))/(p01(1)-p00(1)); %Angular coefficent of the line (m)
    q=p01(2)-m*p01(1); %Intercept of the line (q)
    coefficienti(n,1)=m;
    coefficienti(n,2)=q;
    Qtot=sqrt(a2(n,6)^2+DeltaQ^2); %Sigma q
    Mtot=sqrt(tan_theta^2+a2(n,4)^2); %Sigma m
    
    for sim=1:1000 %Simulation of 10^5 line
       %Values generated with a gaussian pdf with centre in q(m)+/- sigma_q(sigma_m)
       Q = q + (randn(1)*Qtot);
       M = (randn(1)*Mtot)*Q/100 + m;

    %Filling the matrix
    for i=1:372 %line
    for j=1:372 %column
        if floor(M*(j-186)+Q)==-i+186
            s.a(n).b(i,j)=s.a(n).b(i,j)+150;    
        end
    end
    end
    end
end

%Compute product for each element of matrix
I = ones(372);
for n=2:5 %---AIR MEASUREMENTS
%for n=1:5 %---H2O MEASUREMENTS
%for n=1:4 %---NaCl MEASUREMENTS 
for i=1:372
    for j=1:372
        I(i,j)= I(i,j)*s.a(k).b(i,j);
    end
end
end

%Inversion of the lines (y axis) for graphical purposes only (contourf) 
for i=1:372 %line
    for j=1:372 %column
        b(373-i,j)=I(i,j);
            
    end
end
figure %Plot 2D
contourf(b,'lines','none')
colorbar

%-2ln(Likelihood) and plot
c = -2*log(b);
figure
surf(c,'EdgeColor','none');
X=1:1:372;
Y=1:1:372;
%-----------------------------------------------------
%Then fitting with CurveFitter tool