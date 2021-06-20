using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace laba_8
{
    class Program
    {
        public class matrix<T>
        //where T: int, double
        {
            private int n_, m_;
            public T[,] mat;

            public int N { get { return n_; } }
            public int M { get { return m_; } }

            public matrix(int n, int m, T[,] ar)
            {
                this.n_ = n;
                this.m_ = m;
                mat = ar;
            }

            public matrix(int n, int m)
            {
                this.n_ = n;
                this.m_ = m;
                mat = new T[n,m];
            }

            public bool IsSameN(matrix<T> i1)
            {
                return (i1.N == this.N);
            }

            public bool IsSameM(matrix<T> i1)
            {
                return (i1.M == this.M);
            }

            public T retEl(int i, int j)
            {
                return this.mat[i, j];
            }

            public bool isSqer()
            {
                return this.n_ == this.m_;
            }

            public static matrix<T> operator + (matrix<T> m1, matrix<T> m2)
            {
                if (m1.IsSameN(m2) && m1.IsSameM(m2))
                {
                    T[,] ret = new T[m1.N, m1.M];
                    for (int N = 0; N < m1.N; N++)
                        for (int M = 0; M < m1.M; M++)
                        {
                            ret[N, M] = (dynamic)m1.retEl(N, M) + (dynamic)m2.retEl(N, M);
                        }
                    return new matrix<T>(m1.N, m1.M,   ret);
                }
                else
                    return default(matrix<T>);
            }

            public static matrix<T> operator ! (matrix<T> y)
            {
                T[,] ret = new T[y.M, y.N];
                for (int N = 0; N < y.M; N++)
                    for (int M = 0; M < y.N; M++)
                        ret[N, M] = y.retEl(M, N);
                return new matrix<T>(y.M, y.N,   ret);
            }

            public static matrix<T> operator * (matrix<T> m1, matrix<T> m2)
            {
                if (m1.M == m2.N)
                {
                    T[,] ret = new T[m1.N, m2.M];
                    for (int N = 0; N < m1.N; N++)
                        for (int M = 0; M < m2.M; M++)
                            for (int K = 0; K < m1.M; K++)
                                ret[N, M] += (dynamic)m1.mat[N, K] * (dynamic)m2.mat[K, M];
                    return new matrix<T>(m1.N, m2.M,   ret);
                }
                else
                {
                    if ((m1.N == m2.M))
                    {
                        Console.WriteLine("try to multiply matrices in a different order? y/n");
                        if (Console.ReadKey(true).Key == ConsoleKey.Y)
                            return m2 * m1;
                        else
                            return default(matrix<T>);
                    }
                    else
                        return default(matrix<T>);
                }
            }

            private matrix<T> CreateMatrixWithoutColumn(int column)
            {
                if (column < 0 || column >= this.N)
                {
                    throw new ArgumentException("invalid column index");
                }
                var result = new matrix<T>(this.N, this.M - 1);
                int M2;
                for (int N = 0; N < this.N; N++)
                    for (int M = 0; M < this.M-1; M++)
                    {
                        if (M >= column)
                            M2 = M + 1;
                        else
                            M2 = M;
                        result.mat[N, M] = this.mat[N, M2];
                    }
                        return result;
            }

            private matrix<T> CreateMatrixWithoutRow(int row)
            {
                if (row < 0 || row >= this.M)
                {
                    throw new ArgumentException("invalid row index");
                }
                var result = new matrix<T>(this.N - 1, this.M);
                int N2;
                for (int N = 0; N < this.N-1; N++)
                    for (int M = 0; M < this.M; M++)
                    {
                        if (N >= row)
                            N2 = N + 1;
                        else
                            N2 = N;
                        result.mat[N, M] = this.mat[N2, M];
                    }
                return result;
            }

            public double CalculateDeterminant()
            {
                if (!this.isSqer())
                {
                    throw new InvalidOperationException(
                        "determinant can be calculated only for square matrix");
                }
                if (this.M == 2)
                {
                    return ((dynamic)this.mat[0, 0] * this.mat[1, 1] - (dynamic)this.mat[0, 1] * this.mat[1, 0]);
                }
                double result = 0.0;
                for (var j = 0; j < this.N; j++)
                {
                    result += (j % 2 == 1 ? 1 : -1) * (dynamic)this.mat[1, j] * this.CreateMatrixWithoutColumn(j).CreateMatrixWithoutRow(1).CalculateDeterminant();
                }
                return result;
            }

            public void GetMat()
            {
                for (int N = 0; N < this.N; N++)
                    for (int M = 0; M < this.M; M++)
                    {
                        if (M == 0)
                            Console.Write("\n");
                        Console.Write("{0} ", this.retEl(N, M));
                    }
                Console.WriteLine();
            }

        }

        static void Main(string[] args)
        {
            int[,] k = { { 1, 2 }, { 3, 4 } };
            int[,] k1 = { { 10, 20 }, { 30, 40 } };
            int[,] k2 = { { 1, 3, 4}, { 4, 5, 6} };
            int[,] k3 = { { 1, 3, 4 }, { 4, 15, 6 }, { 8, 5, 9 } };
            var mat1 = new matrix<int>(2, 2,   k);
            var mat2 = new matrix<int>(2, 2,   k1);
            var mat6 = new matrix<int>(2, 3,   k2);
            var mat10 = new matrix<int>(3, 3,   k3);
            Console.WriteLine(mat10.CalculateDeterminant());
            mat6.GetMat();
            mat1.GetMat();
            matrix<int> mat3 = !mat1;
            mat3.GetMat();
            matrix<int> mat4 = mat1 + mat2;
            mat4.GetMat();
            matrix<int> mat5 = mat1 * mat2;
            mat5.GetMat();
            matrix<int> mat8 = !mat6;
            mat8.GetMat();
            matrix<int> mat7 = mat8 * mat6;
            mat7.GetMat();
            matrix<int> mat9 = mat2 * mat8;
            mat9.GetMat();
            Console.ReadKey();

        }
    }
}
