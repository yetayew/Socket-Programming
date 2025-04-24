import java.awt.*;
import javax.swing.*;
import java.awt.event.*;
public class SCalculator extends JFrame {
    private JPanel mp;
    private JPanel lp;
    private JPanel up;

    private JButton addition;
    private JButton substraction;
    private JButton division;
    private JButton multiplication;
    private JButton one;
    private JButton two;
    private JButton three;
    private JButton four;
    private JButton five;
    private JButton six;
    private JButton seven;
    private JButton eight;
    private JButton nine;
    private JButton zero;
    private JButton modulSimpole;
    private JButton dot;
    private JButton equSign;

    private JTextField in1;
    private JTextField in2;

    private JLabel result;

public SCalculator() {
super("Simple_Calculator");
setSize(800, 700);
setLocation(300,50);
//getContentPane().add(result);
setDefaultCloseOperation(EXIT_ON_CLOSE);
setVisible(true);
Container c=getContentPane();
    mp=new JPanel();
    up=new JPanel();
    lp=new JPanel();

    addition=new JButton("+");
    substraction=new JButton("-");
    division=new JButton("/");
    multiplication=new JButton("x");
    one=new JButton("1");
    two=new JButton("2");
    three=new JButton("3");
    four=new JButton("4");
    five=new JButton("5");
    six=new JButton("6");
    seven=new JButton("7");
    eight=new JButton("8");
    nine=new JButton("9");
    zero=new JButton("0");
    modulSimpole=new JButton("%");
    dot=new JButton(".");
    equSign=new JButton("=");

    in1=new JTextField("input 1");
    in2=new JTextField("input 2");


    result=new JLabel("answer");

    c.add(result,BorderLayout.NORTH);
    mp.setLayout(new GridLayout(2,1));
    c.add(mp,BorderLayout.CENTER);
    up.setLayout(new GridLayout(1,2));
    lp.setLayout(new GridLayout(4,4,5,5));
    mp.add(up);
    mp.add(lp);
    up.add(in1);
    up.add(in2);
    lp.add(one);
    lp.add(two);
    lp.add(three);
    lp.add(addition);
    lp.add(four);
    lp.add(five);
    lp.add(six);
    lp.add(substraction);
    lp.add(seven);
    lp.add(eight);
    lp.add(nine);
    lp.add(multiplication);
    lp.add(dot);
    lp.add(zero);
    lp.add(equSign);
    lp.add(division);
    addition.addActionListener(new Listener());
    substraction.addActionListener(new Listener());
    multiplication.addActionListener(new Listener());
    division.addActionListener(new Listener());
    one.addActionListener(new Listener());
    two.addActionListener(new Listener());
    three.addActionListener(new Listener());
    four.addActionListener(new Listener());
    five.addActionListener(new Listener());
    six.addActionListener(new Listener());
    seven.addActionListener(new Listener());
    eight.addActionListener(new Listener());
    nine.addActionListener(new Listener());
    zero.addActionListener(new Listener());
    equSign.addActionListener(new Listener());
    dot.addActionListener(new Listener());

}
private class Listener implements ActionListener{
    public void actionPerformed(ActionEvent click){
        if(click.getSource()==one){
           double initial=Double.parseDouble(""+in1.getText());
           double last=Double.parseDouble(""+in2.getText());
           in1.setText(""+1);in2.setText(""+1);
        }
        if(click.getSource()==two){
            double initial=Double.parseDouble(""+in1.getText());
            double last=Double.parseDouble(""+in2.getText()); 
            in1.setText(""+2);in2.setText(""+2);
        }
        
        if(click.getSource()==three){
            double initial=Double.parseDouble(""+in1.getText());
            double last=Double.parseDouble(""+in2.getText());
            in1.setText(""+3);in2.setText(""+3);
        }
        if(click.getSource()==four){
            double initial=Double.parseDouble(""+in1.getText());
            double last=Double.parseDouble(""+in2.getText());
            in1.setText(""+4);in2.setText(""+4);
        }
        if(click.getSource()==five){
            double initial=Double.parseDouble(""+in1.getText());
            double last=Double.parseDouble(""+in2.getText());
            in1.setText(""+5);in2.setText(""+5);
        }
        if(click.getSource()==six){
            double initial=Double.parseDouble(""+in1.getText());
            double last=Double.parseDouble(""+in2.getText());
            in1.setText(""+6);in2.setText(""+6);
        }
        if(click.getSource()==seven){
            double initial=Double.parseDouble(""+in1.getText());
            double last=Double.parseDouble(""+in2.getText());
            in1.setText(""+7);in2.setText(""+7);
        }
        if(click.getSource()==eight){
            double initial=Double.parseDouble(""+in1.getText());
            double last=Double.parseDouble(""+in2.getText());
           in1.setText(""+8);in2.setText(""+8);
        }
        if(click.getSource()==nine){
            double initial=Double.parseDouble(""+in1.getText());
            double last=Double.parseDouble(""+in2.getText());
            in1.setText(""+9);in2.setText(""+9);
        }
        if(click.getSource()==zero){
            double initial=Double.parseDouble(""+in1.getText());
            double last=Double.parseDouble(""+in2.getText());
            in1.setText(""+0);in2.setText(""+0);
        }
        if(click.getSource()==addition){
            double initial=Double.parseDouble(""+in1.getText());
            double last=Double.parseDouble(""+in2.getText());
            double sum=initial+last;
            result.setText(""+sum);
        }
        if(click.getSource()==substraction){
            double initial=Double.parseDouble(""+in1.getText());
            double last=Double.parseDouble(""+in2.getText());
            double sum=initial-last;
            result.setText(""+sum);
        }
        if(click.getSource()==multiplication){
            double initial=Double.parseDouble(""+in1.getText());
            double last=Double.parseDouble(""+in2.getText());
            double sum=initial*last;
            result.setText(""+sum);
        }
        if(click.getSource()==division){
            double initial=Double.parseDouble(""+in1.getText());
            double last=Double.parseDouble(""+in2.getText());
            double sum=initial/last;
            result.setText(""+sum);
        }
        }}
public static void main (String args[]) {
 SCalculator C=new SCalculator();
 C.setVisible(true);
}
}
