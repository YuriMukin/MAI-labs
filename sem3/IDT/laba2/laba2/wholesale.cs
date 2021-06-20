using System;

class wholesale: sales
{
    private string type;
    public wholesale(string castomer, string productnam, double price, int quantity) : base(castomer, productnam, price, quantity)
    {
        this.type = "wholesale";
    }

    public int discount()
    {
        int k=0,t=1, n;
        n = this.quantity;
        while (n / 10 !=  0)
        {
            k++;
            t *= 10;
            n /= 10;
        }
        if ((k >= 6) && (this.quantity * 10 / t < 5))
            return this.quantity * 10 / t;
        else if ((k >= 6) && (this.quantity * 10 / t >= 5))
            return 50;
        else
            return this.quantity / t;
    }

    public override double summ()
    {
        return this.quantity * (this.price - this.price * this.discount() / 100);
    }

    public override string info()
    { 
        return string.Format("{0,-20} {1,-20} {2,10} {3,-10} {4,4}% {5,11}", this.productnam, this.customer, this.price, this.quantity, this.discount(), this.summ());
    }
}
