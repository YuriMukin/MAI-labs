function main()
{
    let canvas = document.querySelector("#scene3d");
    let scene = canvas.getContext("2d");
    let rangeSectorStep = document.querySelector("#approximation");
    let rangeHeight = document.querySelector("#height");
    let rangeRadius = document.querySelector("#radius");
    let sectorStepSphere = 16;
    let heightSphere = 0.5;
    let RadiusSphere = 0.8;


    let drag = false;
    let oldX; let oldY;
    let rotX = 0.; let rotY = 0.;
    let scale = 0.9;
    let mouseDownHandler = function (e)
    {
        drag = true;
        oldX = e.pageX;
        oldY = e.pageY;
        e.preventDefault();
    }
    let mouseUpHandler = function (e)
    {
        drag = false;
        e.preventDefault();
    }
    let mouseMoveHandler = function (e)
    {
        if (!drag)
        {
            return false;
        }

        let newX = oldX - e.pageX;
        let newY = oldY - e.pageY;

        rotX += newX * 2 * Math.PI / canvas.clientWidth;
        rotY += newY * 2 * Math.PI / canvas.clientHeight;

        oldX = e.pageX;
        oldY = e.pageY;

        e.preventDefault();
    }
    let wheelHandler = function (e)
    {
        scale += e.deltaY/1000;
        e.preventDefault();
    }

    let rangeHeightHandler = function (e)
    {
        heightSphere = rangeHeight.value;
    }

    let rangeRadiusHandler = function (e)
    {
        RadiusSphere = rangeRadius.value;
    }

    let rangeHandler = function (e)
    {
        sectorStepSphere = rangeSectorStep.value;
    }

    rangeRadius.addEventListener("input", rangeRadiusHandler, false);
    rangeHeight.addEventListener("input", rangeHeightHandler, false);
    rangeSectorStep.addEventListener("input", rangeHandler, false);
    canvas.addEventListener("mousedown", mouseDownHandler, false);
    canvas.addEventListener("mouseup", mouseUpHandler, false);
    canvas.addEventListener("mouseout", mouseUpHandler, false);
    canvas.addEventListener("mousemove", mouseMoveHandler, false);
    canvas.addEventListener('wheel',wheelHandler, false);

    let drawScene = function(time)
    {
        if(heightSphere>RadiusSphere)
        {
            heightSphere = RadiusSphere
        }
        let points = getPoints(sectorStepSphere, RadiusSphere, heightSphere);
        scene.clearRect(0,0,canvas.clientHeight,canvas.clientWidth);
        for (let i = 0; i<points.length; i+=9)
        {
            let trianglePoints = [];
            for (let j = 0; j<9; j++)
            {
                trianglePoints.push(points[i+j]);
            }
            let angles = [rotY, rotX, 0];
            drawTriangle(scene, trianglePoints, angles, scale);
        }
        requestAnimationFrame(drawScene);

    }

    requestAnimationFrame(drawScene);

}


function drawTriangle(scene, trianglePoints, angles, scale)
{
    let point1 = [trianglePoints[0], trianglePoints[1], trianglePoints[2]]; // [x,y,z]
    let point2 = [trianglePoints[3], trianglePoints[4], trianglePoints[5]];
    let point3 = [trianglePoints[6], trianglePoints[7], trianglePoints[8]];

    point1 = functions3d.rotatePoint(point1, angles)
    point2 = functions3d.rotatePoint(point2, angles)
    point3 = functions3d.rotatePoint(point3, angles)
    let normal = getNormal(point1,point2,point3);
    point1 = functions3d.projectPointTo2d(point1, scale);
    point2 = functions3d.projectPointTo2d(point2, scale);
    point3 = functions3d.projectPointTo2d(point3, scale);
    let light =Math.abs(functions3d.dot(functions3d.normalize(normal),functions3d.normalize([0,0,-1])));
    let g = String(Math.floor(0.5*1*light));
    let r = String(Math.floor(150*1*light));
    let b = String(Math.floor(120*1*light));
    let color = "rgb("+r+","+g+","+b+")";
    scene.strokeStyle = color;
    point1 = convertToPixels(point1, scene.canvas.height, scene.canvas.width);
    point2 = convertToPixels(point2, scene.canvas.height, scene.canvas.width);
    point3 = convertToPixels(point3, scene.canvas.height, scene.canvas.width);
    if (isVisible(point1,point2,point3)) {
        scene.fillStyle = color;
        scene.beginPath()
        scene.moveTo(point1[0], point1[1]);
        scene.lineTo(point2[0], point2[1]);
        scene.lineTo(point3[0], point3[1]);
        scene.lineTo(point1[0], point1[1]);
        scene.fill();
        scene.closePath();
        scene.stroke();
    }
}



function getNormal(point1, point2, point3)
{
    let vector1 = [point2[0]-point1[0], point2[1]-point1[1], point2[2]-point1[2]];
    let vector2 = [point3[0]-point1[0], point3[1]-point1[1], point3[2]-point1[2]];
    let x1 = vector1[0], x2 = vector2[0];
    let y1 = vector1[1], y2 = vector2[1];
    let z1 = vector1[2], z2 = vector2[2];
    let xNorm = y1*z2-y2*z1;
    let yNorm = -(x1*z2-x2*z1);
    let zNorm = x1*y2 - x2*y1;
    return [xNorm,yNorm,zNorm];
}

function isVisible(point1,point2,point3)
{
    let vector1 = [point2[0]-point1[0], point2[1]-point1[1], point2[2]-point1[2]];
    let vector2 = [point3[0]-point1[0], point3[1]-point1[1], point3[2]-point1[2]];
    let x1 = vector1[0], x2 = vector2[0];
    let y1 = vector1[1], y2 = vector2[1];
    let zNorm = x1*y2 - x2*y1;
    return zNorm<0;
}


function convertToPixels(point, canvasHeight, canvasWidth)
{
    let x = ((point[0] + 1) / 2) * canvasWidth;
    let y = ((-point[1] + 1) / 2) * canvasHeight;
    return [x, y];
}

function getPoints(sectorStep, Radius, height)
{
    let PointSet = [];
    let Circles = GenCircleR(sectorStep, Radius, height);
    for(let j=0; j<=sectorStep; j++)
    {
        let CrTop = GenCircle(Circles[j].X,Circles[j].Y,sectorStep);
        let CrDown = GenCircle(Circles[j+1].X,Circles[j+1].Y,sectorStep);
        for(let i=1; i<=sectorStep; i++)
        {
            if (j==0)
            {
                PointSet.push(CrTop[i - 1].X); PointSet.push(CrTop[i - 1].Y); PointSet.push(CrTop[i - 1].Z);
                PointSet.push(0); PointSet.push(CrTop[i].Y); PointSet.push(0);
                PointSet.push(CrTop[i].X); PointSet.push(CrTop[i].Y); PointSet.push(CrTop[i].Z);
            }
            if(j==sectorStep)
            {
                PointSet.push(0); PointSet.push(CrDown[i].Y); PointSet.push(0);
                PointSet.push(CrDown[i - 1].X); PointSet.push(CrDown[i - 1].Y); PointSet.push(CrDown[i - 1].Z);
                PointSet.push(CrDown[i].X); PointSet.push(CrDown[i].Y); PointSet.push(CrDown[i].Z);
            }
            PointSet.push(CrTop[i - 1].X); PointSet.push(CrTop[i - 1].Y); PointSet.push(CrTop[i - 1].Z);
            PointSet.push(CrTop[i].X); PointSet.push(CrTop[i].Y); PointSet.push(CrTop[i].Z);
            PointSet.push(CrDown[i].X); PointSet.push(CrDown[i].Y); PointSet.push(CrDown[i].Z);

            PointSet.push(CrDown[i - 1].X); PointSet.push(CrDown[i - 1].Y); PointSet.push(CrDown[i - 1].Z);
            PointSet.push(CrTop[i - 1].X); PointSet.push(CrTop[i - 1].Y); PointSet.push(CrTop[i - 1].Z);
            PointSet.push(CrDown[i].X); PointSet.push(CrDown[i].Y); PointSet.push(CrDown[i].Z);
        }
    }
    return PointSet;
}

function GenCircleR(pr, Radius, height)
{
    let k = pr / 2;
    let res = [];
    let tmp = height / k;
    for (let i = 0; i<=k; i++)
    {
        res.push(new Point({x: Radius*Math.sin(Math.acos(tmp*i/Radius)), y: -tmp*i, z: 0}));
    }
    for (let i = 0; i<=k; i++)
    {
        res.unshift(new Point({x: Radius*Math.sin(Math.acos(tmp*i/Radius)), y: tmp*i, z: 0}));
    }
    return res;
}

function GenCircle(R, Y, nVert)
{
    let alpha = 6.28318530718 / nVert;
    let vert = [];
    let X, Z;
    for (let i = 0; i <= nVert; i++)
    {
        X = R * Math.sin(alpha * i);
        Z = R * Math.cos(alpha * i);
        if (Math.abs(X) < 0.001)
            X = 0;
        if (Math.abs(Z) < 0.001)
            Z = 0;
        vert.push(new Point({x: X, y: Y, z: Z}));
    }
    return vert;
}

class Point
{
    constructor(param)
    {
        this._X = param.x;
        this._Y = param.y;
        this._Z = param.z;
    }

    get X()
    {
        return this._X;
    }

    get Y()
    {
        return this._Y;
    }

    get Z()
    {
        return this._Z;
    }
}

let functions3d = {

    dot: function (a, b)
    {
        return a[0]*b[0]+a[1]*b[1]+a[2]*b[2];
    },

    projectionAndScale: function(scale)
    {
        let matrix = [
                [scale, 0, 0],
                [0, scale, 0],
            ];
        return matrix;
    },


    matMul: function(A, B) {
        let rowsA = A.length, colsA = A[0].length,
            rowsB = B.length, colsB = B[0].length,
            C = [];
        let temp;

        if (colsA !== rowsB)
        {
            alert("Ошибка");
            console.log("Невозможно умножить матрицы");
            return null;
        }

        for (let i = 0; i < rowsA; i++)
        {
            C[i] = [];
        }
        for (let i = 0; i < rowsA; i++)
        {
            for (let j = 0; j < colsB; j++)
            {
                temp = 0;
                for (let k = 0; k < colsA; k++)
                {
                    temp += A[i][k] * B[k][j]
                }
                C[i][j] = temp;
            }
        }
        return C;
    },

    pointToMatrix: function(point) {
        let matrix = [[],[],[]];
        matrix[0][0] = point[0];
        matrix[1][0] = point[1];
        if (point.length === 3)
        {
            matrix[2][0] = point[2];
            return matrix;
        }
        matrix[2][0] = 0;
        matrix.pop();
        return matrix;

    },

    matToPoint: function(matrix) {
        let x = matrix[0][0];
        let y = matrix[1][0];
        if (matrix.length === 3) {
            let z = matrix[2][0];
            return [x, y, z];
        }
        return [x, y];
    },

    matrixRotateZ: function (angle) {
        let matrix = [
            [Math.cos(angle), -Math.sin(angle), 0],
            [Math.sin(angle), Math.cos(angle), 0],
            [0, 0, 1],
        ];
        return matrix;
    },

    matrixRotateY: function (angle)
    {
        let matrix = [
            [Math.cos(angle), 0, -Math.sin(angle)],
            [0, 1, 0],
            [Math.sin(angle), 0, Math.cos(angle)],
        ];

        return matrix;
    },

    matrixRotateX: function (angle) {
        let matrix = [
            [1, 0, 0],
            [0, Math.cos(angle), -Math.sin(angle)],
            [0, Math.sin(angle), Math.cos(angle)],
        ];
        return matrix;
    },

    rotateZ: function(point, angle) {
        point = this.pointToMatrix(point);
        let rotatedPoint = this.matToPoint(this.matMul(this.matrixRotateZ(angle), point));
        return rotatedPoint;
    },

    rotateY: function (point, angle) {
        point = this.pointToMatrix(point);
        let rotatedPoint = this.matToPoint(this.matMul(this.matrixRotateY(angle), point));
        return rotatedPoint;
    },


    rotateX: function(point, angle) {
        point = this.pointToMatrix(point);
        let rotatedPoint = this.matToPoint(this.matMul(this.matrixRotateX(angle), point));
        return rotatedPoint;
    },

    projectPointTo2d: function(point, scale) {
        point = this.pointToMatrix(point)
        let projectedPoint = this.matToPoint(this.matMul(this.projectionAndScale(scale), point));
        return projectedPoint;
    },

    rotatePoint: function(point, angles) {
        point = this.rotateX(point, angles[0]);
        point = this.rotateY(point, angles[1]);
        point = this.rotateZ(point, angles[2]);
        return point;
    },
    normalize: function(v, dst)
    {
        dst = dst || new Float32Array(3);
        let length = Math.sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
        if (length > 0.00001) {
            dst[0] = v[0] / length;
            dst[1] = v[1] / length;
            dst[2] = v[2] / length;
        }
        return dst;
    }
}

main();