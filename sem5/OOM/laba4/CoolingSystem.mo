package CoolingSystem
  model heater
    parameter Real C = 10;
    parameter Real Hr = 200;
    parameter Real T0 = 20;
    Real Q(start = T0*C);
    Real T;
    Real Qout;
    val_in Tt;
    val_out Qo;
    val_out To;
    
  equation
    der(Q) = Hr- Qout;
    T = Q/C;
    Qout = (T-Tt.val)*C;
    Qo.val = Qout;
    To.val = T;
  end heater;

  model heat_pipe
    parameter Real C = 8;
    parameter Real Ea = 0.55;
    parameter Real S = 2;
    parameter Real T0 = 20;
    Real Qt(start = T0*C);
    Real Qd;
    Real T;
    Real Qr;
    val_in Ta;
    val_in Qh;
    val_in Tr;
    val_out Qo;
    val_out To;
  
  equation
    der(Qt) = Qh.val - Qr - Qd;
    T = Qt/C;
    Qd = (T - Ta.val)*Ea*S;
    Qr = C*(T - Tr.val);
    Qo.val = Qr;
    To.val = T;
  end heat_pipe;

  model radiator
    parameter Real C = 8;
    parameter Real T0 = 20;
    parameter Real Ea = 0.70;
    parameter Real S = 90;
    Real Qe;
    Real T;
    Real A;
    Real Q(start=T0*C);
    val_in Tp;
    val_in Ta;
    val_in Qi;
    val_out To;
     
  equation
    if Tp.val < 30 then
      A = 1;
    elseif Tp.val < 50 then
      A = 1.5;
    elseif Tp.val < 70 then
      A = 2;
    else
      A = 3;
    end if;
    der(Q) = Qi.val - Qe*A;
    T = Q/C;
    Qe = (T-Ta.val)*Ea*S;
    To.val =  T;
  
  end radiator;

  connector val_out
  output Real val;
  end val_out;

  connector val_in
  input Real val;
  end val_in;

  model Pc
    heater H;
    heat_pipe HP;
    radiator R;
    amb A;
    
  equation
    connect(HP.To, H.Tt);
    connect(H.Qo, HP.Qh);
    connect(R.To, HP.Tr);
    connect(R.Tp,  H.To);
    connect(HP.Qo, R.Qi);
    connect(A.To, HP.Ta);
    connect(A.To, R.Ta);
  annotation(
      experiment(StartTime = 0, StopTime = 100, Tolerance = 1e-6, Interval = 0.002));end Pc;

  model amb
    Real T(start = 19);
    parameter Real O = 0.3;
    parameter Real Tmax = 50;
    parameter Real Tmin = 19;
    val_out To;
    
  equation
    T = ((Tmax+Tmin)/2)+((Tmax-Tmin)/2)*sin(O*time);
    To.val = T;
  end amb;
end CoolingSystem;
