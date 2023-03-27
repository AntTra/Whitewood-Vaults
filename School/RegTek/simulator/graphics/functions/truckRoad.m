function [y, theta] = truckRoad(x)
%    height = 5;
%    offset = 5;
%    slope = 0.05;

%    y = height*(tanh(slope*x-offset)+1);
%    dy = height*slope*sech(offset-slope*x).^2;

    a = 5;
    b = 0.04;
    c = -0.2;
    d = 0.06;

    y = a*exp(sin(b*x))+c*exp(cos(d*x))-a*exp(sin(b*0))-c*exp(cos(d*0));
    dy = a*b*exp(sin(b*x)).*cos(b*x)-c*d*sin(d*x).*exp(cos(d*x));

    theta = atan2(dy,1);
end