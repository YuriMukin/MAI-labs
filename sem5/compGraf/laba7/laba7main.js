function main()
{
    let canvas = document.querySelector("#scene3d");
    let rangeAccuracy = document.querySelector("#accuracy");
    let rangeNOBP = document.querySelector("#NOBP");
    let scene = canvas.getContext("2d");
    let Buton = document.querySelector("#Clear");

    let NumOfP = 5;
    let Accuracy = 0.01;
    let BPoints = [];

    let oldX; let oldY;
    let SHy=0; let SHx=0;
    let IsMove = false;
    let pointGrab = false;
    let pointIndex;
    let scale = 1;

    let mouseDownHandler = function (e)
    {
        if(BPoints.length != NumOfP && e.which == 2)
        {
            let tmpX = e.offsetX*(1/scale)-SHx; let tmpY = e.offsetY*(1/scale)-SHy;
            BPoints.push(new Point({x:tmpX, y: tmpY}));
        }
        if (e.which == 1)
        {
            oldX = e.offsetX; oldY = e.offsetY;
            IsMove = true;
            for (let i = 0; i < NumOfP; i++) 
            {
                if (Math.abs((oldX*(1/scale)-SHx) - BPoints[i].X) <= 5 && Math.abs((oldY*(1/scale)-SHy) - BPoints[i].Y) <= 5) 
                {
                    pointIndex = i;
                    pointGrab = true;
                    IsMove = false;
                    break;
                }
            }
        }
        e.preventDefault();
    }

    let mouseUpHandler = function (e)
    {
        pointGrab = false;
        IsMove = false;
        e.preventDefault();
    }

    let mouseMoveHandler = function (e)
    {
        if (IsMove)
        {
            if ( Math.abs(SHx - oldX + e.offsetX) <= canvas.clientWidth)
            {
                SHx -= oldX - e.offsetX;
                oldX = e.offsetX;
            }
            if (Math.abs(SHy - oldY + e.offsetY) <= canvas.clientHeight)
            {
                SHy -= oldY - e.offsetY;
                oldY = e.offsetY;
            }
        }
        if(pointGrab)
        {
            let tmpX = e.offsetX*(1/scale)-SHx; let tmpY = e.offsetY*(1/scale)-SHy;
            console.log("old:",BPoints[pointIndex].X," ",BPoints[pointIndex].Y,"  new: ", tmpX," ", tmpY);
            BPoints[pointIndex] = new Point({x:tmpX, y: tmpY});
        }
        e.preventDefault();
    }

    let wheelHandler = function (e)
    {
        if (scale - e.deltaY/1000 >=0.5)
            scale -= e.deltaY/1000;
        e.preventDefault();
    }

    let rangeAccuracyHandler = function (e)
    {
        Accuracy = 1/rangeAccuracy.value;
        console.log(Accuracy, '  ', rangeAccuracy.value)
        e.preventDefault();
    }

    let rangeNOBPHandler = function (e)
    {
        NumOfP = rangeNOBP.value;
        oldX=0; oldY=0;
        SHy=0; SHx=0;
        scale = 1;
        BPoints = [];
        e.preventDefault();
    }

    let ButonHandler = function (e)
    {
        BPoints = [];
        oldX=0; oldY=0;
        SHy=0; SHx=0;
        scale = 1;
        e.preventDefault();
    }

    rangeAccuracy.addEventListener("input", rangeAccuracyHandler, false);
    rangeNOBP.addEventListener("input", rangeNOBPHandler, false);
    canvas.addEventListener("mousedown", mouseDownHandler, false);
    canvas.addEventListener("mouseout", mouseUpHandler, false);
    canvas.addEventListener("mouseup", mouseUpHandler, false);
    canvas.addEventListener("mousemove", mouseMoveHandler, false);
    canvas.addEventListener("wheel", wheelHandler, false);
    Buton.addEventListener("mousedown", ButonHandler, false)


    let drawScene = function(time)
    {
        scene.clearRect(0,0,canvas.clientHeight,canvas.clientWidth);
        let arr = [];
        if(BPoints.length == NumOfP)
        {
            arr = BezierCurve(BPoints, Accuracy);
            arr.push(BPoints[NumOfP-1])
        }
        DrawLaoyut(scene, canvas.clientHeight, canvas.clientWidth, scale, SHx, SHy);
        DrawLine(scene, arr, scale, SHx, SHy);
        DrawDots(scene, BPoints, scale, SHx, SHy);
        requestAnimationFrame(drawScene);
    }
    requestAnimationFrame(drawScene);
}

function BernsteinPolynomial(CountOfBP, NumOfBP, Accuracy)
{
    function f(n)
    {
        return (n <= 1) ? 1 : n * f(n - 1);
    }
    return (f(NumOfBP)/(f(CountOfBP)*f(NumOfBP - CountOfBP)))* Math.pow(Accuracy, CountOfBP)*Math.pow(1 - Accuracy, NumOfBP - CountOfBP);
}

function BezierCurve(BasePoints, Accuracy)
{
    let points = [];
    for (let t = 0; t<=1; t=t+Accuracy)
    {
        if(t > 1)
        {
            t = 1;
        }
        let Xtmp = 0;
        let Ytmp = 0;
        for(let i=0; i<BasePoints.length; i++)
        {
            let b = BernsteinPolynomial(i,BasePoints.length-1,t);
            Xtmp += BasePoints[i].X * b;
            Ytmp += BasePoints[i].Y * b;
        }
        points.push(new Point({x:Xtmp, y: Ytmp}));
    }
    return points;
}

function DrawLine(scene, arr, scale, shx, shy)
{
    for (let i = 0; i<arr.length-1; i++)
    {
        scene.beginPath()
        scene.strokeStyle = "rgb("+28+","+100+","+212+")";
        scene.lineWidth = 2;
        scene.moveTo((arr[i].X+shx)*scale, (arr[i].Y+shy)*scale);
        scene.lineTo((arr[i+1].X+shx)*scale, (arr[i+1].Y+shy)*scale);
        scene.closePath();
        scene.stroke();
    }
}

function DrawDots(scene, arr, scale, shx, shy)
{
    for (let i=0; i<arr.length; i++)
    {
        scene.strokeStyle = "rgb("+128+","+0+","+0+")";
        scene.fillStyle = "rgb("+128+","+0+","+0+")";
        scene.beginPath();
        scene.arc((arr[i].X+shx)*scale,(arr[i].Y+shy )*scale,3,0,2*Math.PI);
        scene.fill();
        scene.stroke();
    }
}

function DrawLaoyut(scene, Y, X, scale, shx, shy)
{
    let startX = -X*2; let startY = -Y*2;
    for (let i=1; i<=100; i++)
    {
        scene.strokeStyle = "rgb("+128+","+128+","+128+")";
        scene.lineWidth = 1;
        scene.beginPath()
        scene.moveTo((startX+X/20*i+shx)*scale, startY);
        scene.lineTo((startX+X/20*i+shx)*scale, Y);
        scene.moveTo(startX, (startY+Y/20*i+shy)*scale);
        scene.lineTo(X, (startY+Y/20*i+shy)*scale);
        scene.closePath();
        scene.stroke();
    }
}

class Point
{
    constructor(param)
    {
        this._X = param.x;
        this._Y = param.y;
    }

    get X()
    {
        return this._X;
    }

    get Y()
    {
        return this._Y;
    }
}

main();