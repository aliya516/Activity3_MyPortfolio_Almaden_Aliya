package accountdriver;


import java.util.Random; //will use randomizer for account number (6-digits)

class BankAccount //super class
{
    private final String owner; //attributes
    private double balance;
    private String accountNumber;
    
    public BankAccount(String owner, double initialBalance) //constructor for the attributes
    {
        this.owner = owner;
        this.balance = initialBalance;
        this.accountNumber = generateAccountNumber(); //a method
    }
    
     public boolean withdraw(double amount) //to check if insufficient ang funds or hindi
    {
        if (amount <= balance) 
        {
            balance -= amount;
            return true;
        } 
        else 
        {
            System.out.println("Insufficient funds to withdraw $" + amount + ", balance = $" + String.format("%.2f", balance));
            return false;
        }
    }

    public void deposit(double amount)  // to deposit specific amoount and add to the current balance
    {
        balance += amount;
        System.out.println("After Deposit of $" + amount + ", Balance = $" + String.format("%.2f", balance));
    }

    public void printAccountInfo() 
    {
        System.out.println("\nAccount Number " + getAccountNumber() + " belonging to " + owner);
        System.out.println("Initial balance = $" + String.format("%.2f", balance));
    }

    public String getAccountNumber() //getter are for retrieval
    {
        return accountNumber;
    }

    public String getOwner() 
    {
        return owner;
    }

    protected void setAccountNumber(String accountNumber) //to set the account number
    {
        this.accountNumber = accountNumber;
    }

    protected double getBalance() 
    {
        return balance;
    }
    
    protected void setBalance(double balance) {
    this.balance = balance;
}

    private String generateAccountNumber() 
    {
        Random random = new Random();
        int randomValue = random.nextInt(900000) + 100000; //TO GENERATE 6 NUMBERS
        return String.valueOf(randomValue);
    }
}

class CheckingAccount extends BankAccount //1. Create a new class called CheckingAccount that extends BankAccount.
{
    static final double FEE = 0.15; // 2.It should contain a static constant FEE that represents the cost of clearing one check. Set it equal to 15 cents.

    public CheckingAccount(String owner, double initialBalance)// 3. .Write a constructor that takes a name and an initial amount as parameters.
    {
        super(owner, initialBalance);
        setAccountNumber(getAccountNumber() + "-10"); //3.1 It should initialize accountNumber to be the current value in accountNumber concatenated with -10
    }

    @Override //4.Write a new instance method, withdraw, that overrides the withdraw method in the superclass.
  public boolean withdraw(double amount) 
    {
    double totalAmount = amount + FEE;
    boolean success = super.withdraw(totalAmount);
    return success;
    }
}

class SavingsAccount extends BankAccount //1.Create a new class called SavingsAccount that extends BankAccount.
{
    private static final double RATE = 0.025; //2.It should contain an instance variable called rate that represents the annual interest rate. Set it equal to 2.5%.
    private int savingsNumber;//3. instance variable called savingsNumber

    public SavingsAccount(String owner, double initialBalance) 
    {
        super(owner, initialBalance);
        this.savingsNumber = 0;  //3.1 It should also have an instance variable called savingsNumber, initialized to 0.
        setAccountNumber(super.getAccountNumber() + "-" + (this.savingsNumber + 10)); //4.An instance variable called accountNumber
    }

    public SavingsAccount(SavingsAccount originalAccount, double initialBalance) //5.Write a constructor that takes a name and an initial balance as parameters and calls the constructor for the superclass. It should initialize accountNumber tobe the current value in the superclass accountNumber (the hidden instance variable) concatenated with a hyphen and then the savingsNumber.
    {
        super(originalAccount.getOwner(), initialBalance);
        this.savingsNumber = originalAccount.savingsNumber + 1;
        setAccountNumber(super.getAccountNumber() + "-" + this.savingsNumber);
    }

    public void postInterest() //6.Write a method called postInterest that has no parameters and returns no value. This method will calculate one month's worth of interest on the balance and deposit it into the account.
    {
        
        double interest = getBalance() * RATE / 12; 
        setBalance(getBalance() + interest);
        System.out.println("After monthly interest has been posted, balance = $" + String.format("%.2f", getBalance()));
    }

    @Override  //7.Write a method that overrides the getAccountNumber method in the superclass.
    public void printAccountInfo() 
    {
        System.out.println("\nAccount Number " + getAccountNumber().toUpperCase() + " belonging to " + getOwner());
        System.out.println("Initial balance = $" + String.format("%.2f", getBalance()));
    } 
}
        
public class AccountDriver 
{
    public static void main(String[] args) 
    {
        CheckingAccount checkingAccount = new CheckingAccount("Benjamin Franklin", 1000.00);
        checkingAccount.printAccountInfo();
        checkingAccount.deposit(500.00);
        boolean withdrawSuccess = checkingAccount.withdraw(1000.00);
        if (withdrawSuccess) 
        {
            System.out.println("After withdrawal of $1000.00, balance = $" + String.format("%.2f", checkingAccount.getBalance()));
        }

        SavingsAccount savingsAccount = new SavingsAccount("William Shakespeare", 400.00);
        savingsAccount.printAccountInfo();
        savingsAccount.deposit(500.00);  
        savingsAccount.postInterest(); 
        boolean savingsWithdrawSuccess = savingsAccount.withdraw(1000.00);
        
        SavingsAccount anotherSavingsAccount = new SavingsAccount("William Shakespeare", 5.00);
        anotherSavingsAccount.printAccountInfo();
        anotherSavingsAccount.deposit(500.00);
        boolean anotherSavingsWithdrawSuccess = anotherSavingsAccount.withdraw(1000.00);
       
        CheckingAccount specificCheckingAccount = new CheckingAccount ("Isaac Newton", 0.00);
        specificCheckingAccount.printAccountInfo();
        }
}


