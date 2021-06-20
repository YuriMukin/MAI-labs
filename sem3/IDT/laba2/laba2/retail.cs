using System;

class retail: sales
{
    private int discount;
    private string type;

    public retail(string castomer, string productnam, double price, int quantity, int ds): base(castomer, productnam, price, quantity)
    {
        this.discount = ds;
        this.type = "retail";
    }

    public override double summ()
    {
        return this.quantity * (this.price - this.price * this.discount / 100);
    }

    public override string info()
    {
        return string.Format("{0,-20} {1,-20} {2,10} {3,-10} {4,4}% {5,11}", this.productnam, this.customer, this.price, this.quantity, this.discount, this.summ());
    }

}
