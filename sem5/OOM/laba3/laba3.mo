package laba3
  model func1
    Modelica.Electrical.Analog.Basic.Resistor R0(R = 211) annotation(
      Placement(transformation(extent = {{-34, 24}, {-14, 44}})));
    Modelica.Electrical.Analog.Basic.Inductor L0(L = 23) annotation(
      Placement(transformation(extent = {{12, 38}, {32, 58}})));
    Modelica.Electrical.Analog.Basic.Resistor R1(R = 12) annotation(
      Placement(transformation(extent = {{12, 10}, {32, 30}})));
    Modelica.Electrical.Analog.Basic.Capacitor C(C = 0.005) annotation(
      Placement(transformation(extent = {{-10, -10}, {10, 10}}, rotation = -90, origin = {52, 10})));
    Modelica.Electrical.Analog.Basic.Resistor R2(R = 32) annotation(
      Placement(transformation(extent = {{12, -10}, {32, 10}})));
    Modelica.Electrical.Analog.Sources.SineVoltage sineVoltage(freqHz = 50, V = 34) annotation(
      Placement(transformation(extent = {{-10, -10}, {10, 10}}, rotation = -90, origin = {-44, 10})));
    Modelica.Electrical.Analog.Basic.Ground ground annotation(
      Placement(transformation(extent = {{-16, -36}, {4, -16}})));
  equation
    connect(R0.n, L0.p) annotation(
      Line(points = {{-14, 34}, {-2, 34}, {-2, 48}, {12, 48}}, color = {0, 0, 255}, smooth = Smooth.None));
    connect(R0.n, R1.p) annotation(
      Line(points = {{-14, 34}, {-2, 34}, {-2, 20}, {12, 20}}, color = {0, 0, 255}, smooth = Smooth.None));
    connect(L0.n, C.p) annotation(
      Line(points = {{32, 48}, {52, 48}, {52, 20}}, color = {0, 0, 255}, smooth = Smooth.None));
    connect(R1.n, C.p) annotation(
      Line(points = {{32, 20}, {52, 20}}, color = {0, 0, 255}, smooth = Smooth.None));
    connect(C.n, R2.n) annotation(
      Line(points = {{52, 0}, {32, 0}}, color = {0, 0, 255}, smooth = Smooth.None));
    connect(R0.p, sineVoltage.p) annotation(
      Line(points = {{-34, 34}, {-44, 34}, {-44, 20}}, color = {0, 0, 255}, smooth = Smooth.None));
    connect(sineVoltage.n, R2.p) annotation(
      Line(points = {{-44, 0}, {12, 0}}, color = {0, 0, 255}, smooth = Smooth.None));
    connect(ground.p, R2.p) annotation(
      Line(points = {{-6, -16}, {-6, 0}, {12, 0}}, color = {0, 0, 255}, smooth = Smooth.None));
    annotation(
      Diagram(graphics));
  end func1;

  model func2
    Modelica.Electrical.Analog.Basic.Inductor L0(L = 23) annotation(
      Placement(transformation(extent = {{12, 38}, {32, 58}})));
    Modelica.Electrical.Analog.Basic.Resistor R1(R = 12) annotation(
      Placement(transformation(extent = {{12, 10}, {32, 30}})));
    Modelica.Electrical.Analog.Basic.Capacitor C(C = 0.005) annotation(
      Placement(transformation(extent = {{-10, -10}, {10, 10}}, rotation = -90, origin = {52, 10})));
    Modelica.Electrical.Analog.Basic.Resistor R2(R = 32) annotation(
      Placement(transformation(extent = {{12, -10}, {32, 10}})));
    Modelica.Electrical.Analog.Sources.SineVoltage sineVoltage(freqHz = 50, V = 34) annotation(
      Placement(transformation(extent = {{-10, -10}, {10, 10}}, rotation = -90, origin = {-40, 10})));
    Modelica.Electrical.Analog.Basic.Ground ground annotation(
      Placement(transformation(extent = {{-16, -36}, {4, -16}})));
    my_resist R0(R = 234) annotation(
      Placement(transformation(extent = {{-40, 38}, {-20, 58}})));
  equation
    connect(L0.n, C.p) annotation(
      Line(points = {{32, 48}, {52, 48}, {52, 20}}, color = {0, 0, 255}, smooth = Smooth.None));
    connect(R1.n, C.p) annotation(
      Line(points = {{32, 20}, {52, 20}}, color = {0, 0, 255}, smooth = Smooth.None));
    connect(C.n, R2.n) annotation(
      Line(points = {{52, 0}, {32, 0}}, color = {0, 0, 255}, smooth = Smooth.None));
    connect(sineVoltage.n, R2.p) annotation(
      Line(points = {{-40, 0}, {12, 0}}, color = {0, 0, 255}, smooth = Smooth.None));
    connect(ground.p, R2.p) annotation(
      Line(points = {{-6, -16}, {-6, 0}, {12, 0}}, color = {0, 0, 255}, smooth = Smooth.None));
    connect(sineVoltage.p, R0.p) annotation(
      Line(points = {{-40, 20}, {-40, 48}}, color = {0, 0, 255}, smooth = Smooth.None));
    connect(R0.n, L0.p) annotation(
      Line(points = {{-20, 48}, {12, 48}}, color = {0, 0, 255}, smooth = Smooth.None));
    annotation(
      Diagram(graphics));
  end func2;

  model my_resist
    parameter Modelica.SIunits.Resistance R(start = 1) "Resistance at temperature T_ref";
    parameter Modelica.SIunits.Temperature T_ref = 300.15 "Reference temperature";
    parameter Real alpha = 0;
    parameter Modelica.SIunits.Current Io = 1;
    extends Modelica.Electrical.Analog.Interfaces.OnePort;
    extends Modelica.Electrical.Analog.Interfaces.ConditionalHeatPort(T = T_ref);
    Modelica.SIunits.Resistance R_actual;
  equation
    assert(1 + alpha * (T_heatPort - T_ref) >= Modelica.Constants.eps, "Temperature outside scope of model!");
    R_actual = R * (1 + alpha * (1 / Io));
    v = R_actual * i;
    LossPower = v * i;
    annotation(
      Documentation(info = "<html>
<p>The linear resistor connects the branch voltage <i>v</i> with the branch current <i>i</i> by <i>i*R = v</i>. The Resistance <i>R</i> is allowed to be positive, zero, or negative.</p>
</html>", revisions = "<html>
<ul>
<li><i> August 07, 2009   </i>
       by Anton Haumer<br> temperature dependency of resistance added<br>
       </li>
<li><i> March 11, 2009   </i>
       by Christoph Clauss<br> conditional heat port added<br>
       </li>
<li><i> 1998   </i>
       by Christoph Clauss<br> initially implemented<br>
       </li>
</ul>
</html>"),
      Icon(coordinateSystem(preserveAspectRatio = true, extent = {{-100, -100}, {100, 100}}, grid = {2, 2}), graphics = {Rectangle(extent = {{-70, 30}, {70, -30}}, lineColor = {0, 0, 255}, fillColor = {255, 255, 255}, fillPattern = FillPattern.Solid), Line(points = {{-90, 0}, {-70, 0}}, color = {0, 0, 255}), Line(points = {{70, 0}, {90, 0}}, color = {0, 0, 255}), Text(extent = {{-144, -40}, {142, -72}}, lineColor = {0, 0, 0}, textString = "R=%R"), Line(visible = useHeatPort, points = {{0, -100}, {0, -30}}, color = {127, 0, 0}, smooth = Smooth.None, pattern = LinePattern.Dot), Text(extent = {{-152, 87}, {148, 47}}, textString = "%name", lineColor = {0, 0, 255})}),
      Diagram(coordinateSystem(preserveAspectRatio = true, extent = {{-100, -100}, {100, 100}}, grid = {2, 2}), graphics = {Rectangle(extent = {{-70, 30}, {70, -30}}, lineColor = {0, 0, 255}), Line(points = {{-96, 0}, {-70, 0}}, color = {0, 0, 255}), Line(points = {{70, 0}, {96, 0}}, color = {0, 0, 255})}));
  end my_resist;

  model func3
    Modelica.Electrical.Analog.Sources.SineVoltage sineVoltage(V = 230, freqHz = 50) annotation(
      Placement(transformation(extent = {{-10, -10}, {10, 10}}, rotation = 270, origin = {-62, 8})));
    my_resist R0(R = 3450) annotation(
      Placement(transformation(extent = {{-48, 34}, {-28, 54}})));
    my_resist R3(R = 1000) annotation(
      Placement(transformation(extent = {{-6, -26}, {14, -6}})));
    my_resist my_resist3 annotation(
      Placement(transformation(extent = {{2, 34}, {22, 54}})));
    Modelica.Electrical.Analog.Basic.Capacitor C1(C = 0.0005) annotation(
      Placement(transformation(extent = {{0, 54}, {20, 74}})));
    Modelica.Electrical.Analog.Basic.Capacitor C2(C = 0.001) annotation(
      Placement(transformation(extent = {{-10, -10}, {10, 10}}, rotation = -90, origin = {40, 10})));
    Modelica.Electrical.Analog.Basic.Ground ground annotation(
      Placement(transformation(extent = {{-42, -56}, {-22, -36}})));
  equation
    connect(R0.n, C1.p) annotation(
      Line(points = {{-28, 44}, {-14, 44}, {-14, 64}, {0, 64}}, color = {0, 0, 255}, smooth = Smooth.None));
    connect(R0.n, my_resist3.p) annotation(
      Line(points = {{-28, 44}, {2, 44}}, color = {0, 0, 255}, smooth = Smooth.None));
    connect(C1.n, C2.p) annotation(
      Line(points = {{20, 64}, {40, 64}, {40, 20}}, color = {0, 0, 255}, smooth = Smooth.None));
    connect(my_resist3.n, C2.p) annotation(
      Line(points = {{22, 44}, {40, 44}, {40, 20}}, color = {0, 0, 255}, smooth = Smooth.None));
    connect(R3.n, C2.n) annotation(
      Line(points = {{14, -16}, {40, -16}, {40, 0}}, color = {0, 0, 255}, smooth = Smooth.None));
    connect(ground.p, R3.p) annotation(
      Line(points = {{-32, -36}, {-32, -16}, {-6, -16}}, color = {0, 0, 255}, smooth = Smooth.None));
    connect(sineVoltage.p, R0.p) annotation(
      Line(points = {{-62, 18}, {-62, 44}, {-48, 44}}, color = {0, 0, 255}, smooth = Smooth.None));
    connect(sineVoltage.n, R3.p) annotation(
      Line(points = {{-62, -2}, {-62, -16}, {-6, -16}}, color = {0, 0, 255}, smooth = Smooth.None));
    annotation(
      Diagram(graphics));
  end func3;

  model func4
    my_resist R3(R = 2351) annotation(
      Placement(transformation(extent = {{-10, -10}, {10, 10}}, rotation = 270, origin = {54, 8})));
    my_resist R0(R = 1000) annotation(
      Placement(transformation(extent = {{-60, 28}, {-40, 48}})));
    my_resist R2(R = 1200) annotation(
      Placement(transformation(extent = {{22, 12}, {42, 32}})));
    my_resist R1(R = 345) annotation(
      Placement(transformation(extent = {{22, 42}, {42, 62}})));
    Modelica.Electrical.Analog.Basic.Inductor L0(L = 43) annotation(
      Placement(transformation(extent = {{-26, 12}, {-6, 32}})));
    Modelica.Electrical.Analog.Basic.Capacitor C0(C = 0.0045) annotation(
      Placement(transformation(extent = {{-26, 42}, {-6, 62}})));
    Modelica.Electrical.Analog.Sources.SineVoltage sineVoltage(V = 230, freqHz = 50) annotation(
      Placement(transformation(extent = {{-10, -10}, {10, 10}}, rotation = -90, origin = {-72, 8})));
    Modelica.Electrical.Analog.Basic.Ground ground annotation(
      Placement(visible = true, transformation(extent = {{44, -28}, {64, -8}}, rotation = 0)));
  equation
    connect(sineVoltage.p, R0.p) annotation(
      Line(points = {{-72, 18}, {-72, 38}, {-60, 38}}, color = {0, 0, 255}, smooth = Smooth.None));
    connect(R0.n, C0.p) annotation(
      Line(points = {{-40, 38}, {-34, 38}, {-34, 52}, {-26, 52}}, color = {0, 0, 255}, smooth = Smooth.None));
    connect(R0.n, L0.p) annotation(
      Line(points = {{-40, 38}, {-34, 38}, {-34, 22}, {-26, 22}}, color = {0, 0, 255}, smooth = Smooth.None));
    connect(L0.n, R2.p) annotation(
      Line(points = {{-6, 22}, {22, 22}}, color = {0, 0, 255}, smooth = Smooth.None));
    connect(C0.n, R1.p) annotation(
      Line(points = {{-6, 52}, {22, 52}}, color = {0, 0, 255}, smooth = Smooth.None));
    connect(R1.n, R3.p) annotation(
      Line(points = {{42, 52}, {54, 52}, {54, 18}}, color = {0, 0, 255}, smooth = Smooth.None));
    connect(R2.n, R3.p) annotation(
      Line(points = {{42, 22}, {54, 22}, {54, 18}}, color = {0, 0, 255}, smooth = Smooth.None));
    connect(R3.n, sineVoltage.n) annotation(
      Line(points = {{54, -2}, {-72, -2}}, color = {0, 0, 255}, smooth = Smooth.None));
    connect(R3.n, ground.p) annotation(
      Line(points = {{54, -2}, {54, -8}}, color = {0, 0, 255}));
    annotation(
      Diagram(graphics));
  end func4;
  annotation(
    uses(Modelica(version = "3.2")));
end laba3;
