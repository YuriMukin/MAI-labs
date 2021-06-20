using System;

abstract class sales
{
    protected string productnam;
    protected string customer;
    protected int quantity;
    protected double price;
    abstract public double summ();
    abstract public string info();
    public sales (string customer, string productnam, double price, int quantity)
    {
        this.productnam = productnam;
        this.customer = customer;
        this.quantity = quantity;
        this.price = price;
    }
}
