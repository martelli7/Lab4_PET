%Finding coordinates x,y errors by projecting the ellipse extremes
x=[];
y=[];
X=[];
Y=[];
minimo = min(min(c));
%Ellipse matric, found at (paraboloid minimum + 2.3) with respect to z
%axis
ell=zeros(372); %ellipse
for i=1:372
    for j=1:372
        if c(i,j)<= minimo+2.3
            ell(i,j)=1; 
    end
end
end
%Ellipse points coordinates
for i=1:372
    for j=1:372
        if ell(i,j)~=0
            x(i)=i;
            y(j)=j;
        end
    end
end
I=1;
J=1;
for i=1:length(x)
    if x(i)~=0
        X(I)=x(i);
        I=I+1;
    end
end
for i=1:length(y)
    if y(i)~=0
        Y(J)=y(i);
        J=J+1;
    end
end
%Errors evalutation 
Xerr=(max(X)-min(X))/2
Yerr=(max(Y)-min(Y))/2  

%Slope angle of the ellipses depends on the slope of the lines
media=0;
for n=2:5 %---AIR MEASUREMENTS
%for n=1:5 %---H2O MEASUREMENTS
%for n=1:4 %---NaCl MEASUREMENTS 
media=media+coefficienti(i,1);
end
media =media/4 %AIR and NaCl
%media =media/5 %H2O
AngoloEllisse= rad2deg(atan(media))
XC=116; %coordinate X of the paraboloid centre (from the FIT)
YC=121.5; %coordinate Y of the paraboloid centre (from the FIT)

%Source angular coordinate with respect to the centre
alfa = 180+atan((YC-186)/(XC-186))*180/pi

%Covaraince of x and y
covXY=(tan(2*atan(media))*(Yerr^2-Xerr^2))/2;
sigmaXY=sqrt(abs(covXY))