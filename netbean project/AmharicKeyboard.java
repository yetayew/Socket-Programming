import java.awt.FlowLayout;
import java.awt.*;
import javax.swing.*;
import javax.swing.SwingUtilities;
import java.awt.event.*;
import java.io.*;
import java.io.PrintStream;

public class AmharicKeyboard extends JFrame {

    private JPanel first;
    private JPanel second;
    private JPanel third;
    private JPanel sixth;
    private JPanel fourth;
    private JPanel fifth;
    private JMenuBar menuBar;
    private JMenuBar fileMenu;

    private JButton A;
    private JButton O;
    private JButton E;
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
    private JButton q;
    private JButton b;
    private JButton c;
    private JButton d;
    private JButton f;
    private JButton g;
    private JButton h;
    private JButton j;
    private JButton k;
    private JButton l;
    private JButton m;
    private JButton p;
    private JButton r;
    private JButton t;
    private JButton s;
    private JButton v;
    private JButton w;
    private JButton x;
    private JButton y;
    private JButton z;
    private JButton B;
    private JButton C;
    private JButton D;
    private JButton F;
    private JButton G;
    private JButton H;
    private JButton J;
    private JButton K;
    private JButton L;
    private JButton N;
    private JButton M;
    private JButton P;
    private JButton Q;
    private JButton R;
    private JButton S;
    private JButton T;
    private JButton V;
    private JButton W;
    private JButton X;
    private JButton Y;
    private JButton Z;
    private JButton n;
    private JButton up;
    private JButton full;
    private JButton clear;
    private JButton colon;
    private JButton dot;
    private JButton coma;
    private JButton EN;
    private JButton space;
    private JButton ENTER;
    private JButton DIGIT;
    private JButton KEY;

    private JTextField in1;
    private JLabel result;

    public AmharicKeyboard() {
        setTitle("አማረኛ Amharic_Keyboard");
        setSize(600, 600);
        setLocation(500, 200);
        //getContentPane().add(result);
        setDefaultCloseOperation(EXIT_ON_CLOSE);
        setVisible(true);
        Container cont = getContentPane();
        cont.setBackground(Color.YELLOW);
        menuBar = new JMenuBar();
        //JMenu fileMenu = new JMenu("A");
         //menuBar.add(fileMenu);
        //JMenuItem newMenuItem = new JMenuItem("two");
        //JMenuItem nuItem = new JMenuItem("three");
        //setJMenuBar(menuBar);
        //newMenuItem.addActionListener(new Listener());
       // fileMenu.add(newMenuItem);
        // fileMenu.add(nuItem);

        first = new JPanel();
        second = new JPanel();
        third = new JPanel();
        fourth = new JPanel();
        fifth = new JPanel();
        sixth = new JPanel();

        A = new JButton("A");
        E = new JButton("E");
        O = new JButton("O");
        one = new JButton("1");
        two = new JButton("2");
        three = new JButton("3");
        four = new JButton("4");
        five = new JButton("5");
        six = new JButton("6");
        seven = new JButton("7");
        eight = new JButton("8");
        nine = new JButton("9");
        zero = new JButton("0");
        dot = new JButton(".");
        up = new JButton("" + '\u27F8');
        colon = new JButton(":");
        full = new JButton("::");
        clear = new JButton("" + '\u274E');
        space = new JButton("[_______]");
        EN = new JButton("EN");
        DIGIT = new JButton("" + '\u1369' + '\u136A' + '\u136B');
        KEY = new JButton("" + '\u2328');
        ENTER = new JButton("Enter " + '\u21A9');

        h = new JButton("" + '\u1200');
        l = new JButton("" + '\u1208');
        H = new JButton("" + '\u1210');
        m = new JButton("" + '\u1218');
        S = new JButton("" + '\u1220');
        r = new JButton("" + '\u1228');
        s = new JButton("" + '\u1230');
        F = new JButton("" + '\u1238');
        q = new JButton("" + '\u1240');
        b = new JButton("" + '\u1260');
        t = new JButton("" + '\u1270');
        c = new JButton("" + '\u1278');
        n = new JButton("" + '\u1290');
        N = new JButton("" + '\u1298');
        x = new JButton("" + '\u12A0');
        k = new JButton("" + '\u12A8');
        K = new JButton("" + '\u12B8');
        z = new JButton("" + '\u12D8');
        Z = new JButton("" + '\u12E0');
        v = new JButton("" + '\u1268');
        y = new JButton("" + '\u12E8');
        w = new JButton("" + '\u12C8');
        d = new JButton("" + '\u12F0');
        j = new JButton("" + '\u1300');
        g = new JButton("" + '\u1308');
        f = new JButton("" + '\u1348');
        p = new JButton("" + '\u1350');
        T = new JButton("" + '\u1320');
        C = new JButton("" + '\u1328');
        P = new JButton("" + '\u1330');
        B = new JButton("" + '\u1338');
        D = new JButton("" + '\u1340');
        Q = new JButton("" + '\u1280');
        X = new JButton("" + '\u12D0');

        in1 = new JTextField("");
        result = new JLabel("your text");

        Font font=new Font("Abyssinica SIL",Font.PLAIN,15);
        in1.setFont(font);
        h.setFont(font);
        super.setFont(font);

        cont.add(result, BorderLayout.NORTH);
        first.setLayout(new GridLayout(1, 1));
        cont.add(first, BorderLayout.CENTER);
        second.setLayout(new GridLayout(2, 1));
        menuBar.setLayout(new GridLayout(2, 1));

        third.setLayout(new GridLayout(3, 10, 5, 5));
        sixth.setLayout(new GridLayout(2, 1));
        fifth.setLayout(new GridLayout(2, 9, 5, 5));
        fourth.setLayout(new GridLayout(1, 6, 5, 5));
        first.add(second);
        second.add(in1);
        menuBar.add(third);
        menuBar.add(sixth);
        second.add(menuBar);
        //second.add(fourth);
        sixth.add(fifth);
        sixth.add(fourth);

        third.add(one);
        third.add(two);
        third.add(three);
        third.add(four);
        third.add(five);
        third.add(six);
        third.add(seven);
        third.add(eight);
        third.add(nine);
        third.add(zero);
        third.add(n);
        third.add(t);
        third.add(b);
        third.add(y);
        third.add(m);
        third.add(x);
        third.add(r);
        third.add(w);
        third.add(l);
        third.add(s);
        third.add(c);
        third.add(g);
        third.add(d);
        third.add(k);
        third.add(T);
        third.add(q);
        third.add(z);
        third.add(h);
        third.add(S);
        third.add(Z);

        fifth.add(f);
        fifth.add(N);
        fifth.add(j);
        fifth.add(F);
        fifth.add(C);
        fifth.add(p);
        fifth.add(P);
        fifth.add(K);
        fifth.add(v);
        fifth.add(up);
        fifth.add(colon);
        fifth.add(X);
        fifth.add(H);
        fifth.add(B);
        fifth.add(D);
        fifth.add(Q);
        fifth.add(full);
        fifth.add(clear);

        fourth.add(KEY);
        fourth.add(DIGIT);
        fourth.add(dot);
        fourth.add(space);
        fourth.add(EN);
        fourth.add(ENTER);

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
        colon.addActionListener(new Listener());
        full.addActionListener(new Listener());
        dot.addActionListener(new Listener());
        up.addActionListener(new Listener());
        clear.addActionListener(new Listener());
        space.addActionListener(new Listener());
        ENTER.addActionListener(new Listener());
        h.addActionListener(new Listener());
        l.addActionListener(new Listener());
        H.addActionListener(new Listener());
        m.addActionListener(new Listener());
        r.addActionListener(new Listener());
        s.addActionListener(new Listener());
        S.addActionListener(new Listener());
        F.addActionListener(new Listener());
        k.addActionListener(new Listener());
        K.addActionListener(new Listener());
        b.addActionListener(new Listener());
        t.addActionListener(new Listener());
        c.addActionListener(new Listener());
        T.addActionListener(new Listener());
        C.addActionListener(new Listener());
        X.addActionListener(new Listener());
        x.addActionListener(new Listener());
        n.addActionListener(new Listener());
        N.addActionListener(new Listener());
        g.addActionListener(new Listener());
        j.addActionListener(new Listener());
        y.addActionListener(new Listener());
        w.addActionListener(new Listener());
        z.addActionListener(new Listener());
        Z.addActionListener(new Listener());
        d.addActionListener(new Listener());
        D.addActionListener(new Listener());
        B.addActionListener(new Listener());
        Q.addActionListener(new Listener());
        q.addActionListener(new Listener());
        v.addActionListener(new Listener());
        p.addActionListener(new Listener());
        P.addActionListener(new Listener());
        f.addActionListener(new Listener());

        pack();
    }

    private class Listener implements ActionListener {

        public void actionPerformed(ActionEvent click) {
            if (click.getSource() == one) {
                in1.setText(in1.getText() + "1");
            }
            if (click.getSource() == two) {
                in1.setText(in1.getText() + "2");

            }
            if (click.getSource() == three) {
                in1.setText(in1.getText() + "3");

            }
            if (click.getSource() == four) {
                in1.setText(in1.getText() + "4");

            }
            if (click.getSource() == five) {
                in1.setText(in1.getText() + "5");

            }
            if (click.getSource() == six) {
                in1.setText(in1.getText() + "6");

            }
            if (click.getSource() == seven) {
                in1.setText(in1.getText() + "7");

            }
            if (click.getSource() == eight) {
                in1.setText(in1.getText() + "8");

            }
            if (click.getSource() == nine) {
                in1.setText(in1.getText() + "9");

            }
            if (click.getSource() == zero) {
                in1.setText(in1.getText() + "0");

            }
            if (click.getSource() == n) {
                in1.setText(in1.getText() + '\u1290');

            }
            if (click.getSource() == t) {
                in1.setText(in1.getText() + '\u1270');

            }
            if (click.getSource() == h) {
                in1.setText(in1.getText() + '\u1200');

            }
            if (click.getSource() == l) {
                in1.setText(in1.getText() + '\u1208');

            }
            if (click.getSource() == H) {
                in1.setText(in1.getText() + '\u1210');

            }
            if (click.getSource() == m) {
                in1.setText(in1.getText() + '\u1218');

            }
            if (click.getSource() == s) {
                in1.setText(in1.getText() + '\u1230');

            }
            if (click.getSource() == r) {
                in1.setText(in1.getText() + '\u1228');

            }
            if (click.getSource() == S) {
                in1.setText(in1.getText() + '\u1220');

            }
            if (click.getSource() == F) {
                in1.setText(in1.getText() + '\u1238');

            }
            if (click.getSource() == q) {
                in1.setText(in1.getText() + '\u1240');

            }
            if (click.getSource() == b) {
                in1.setText(in1.getText() + '\u1260');

            }
            if (click.getSource() == v) {
                in1.setText(in1.getText() + '\u1268');

            }
            if (click.getSource() == c) {
                in1.setText(in1.getText() + '\u1278');

            }
            if (click.getSource() == Q) {
                in1.setText(in1.getText() + '\u1280');

            }
            if (click.getSource() == N) {
                in1.setText(in1.getText() + '\u1298');

            }
            if (click.getSource() == x) {
                in1.setText(in1.getText() + '\u12A0');

            }
            if (click.getSource() == k) {
                in1.setText(in1.getText() + '\u12A8');

            }
            if (click.getSource() == K) {
                in1.setText(in1.getText() + '\u12B8');

            }
            if (click.getSource() == w) {
                in1.setText(in1.getText() + '\u12C8');

            }
            if (click.getSource() == X) {
                in1.setText(in1.getText() + '\u12D0');

            }
            if (click.getSource() == z) {
                in1.setText(in1.getText() + '\u12D8');

            }
            if (click.getSource() == Z) {
                in1.setText(in1.getText() + '\u12E0');

            }
            if (click.getSource() == y) {
                in1.setText(in1.getText() + '\u12E8');

            }
            if (click.getSource() == d) {
                in1.setText(in1.getText() + '\u12F0');

            }
            if (click.getSource() == j) {
                in1.setText(in1.getText() + '\u1300');

            }
            if (click.getSource() == g) {
                in1.setText(in1.getText() + '\u1308');

            }
            if (click.getSource() == T) {
                in1.setText(in1.getText() + '\u1320');

            }
            if (click.getSource() == C) {
                in1.setText(in1.getText() + '\u1328');

            }
            if (click.getSource() == P) {
                in1.setText(in1.getText() + '\u1330');

            }
            if (click.getSource() == B) {
                in1.setText(in1.getText() + '\u1338');

            }
            if (click.getSource() == D) {
                in1.setText(in1.getText() + '\u1340');

            }
            if (click.getSource() == f) {
                in1.setText(in1.getText() + '\u1348');

            }
            if (click.getSource() == dot) {
                in1.setText(in1.getText() + ".");

            }
            if (click.getSource() == full) {
                in1.setText(in1.getText() + "::");

            }
            if (click.getSource() == colon) {
                in1.setText(in1.getText() + ":");

            }
            if (click.getSource() == p) {
                in1.setText(in1.getText() + '\u1350');

            }
            if (click.getSource() == up) {

                //one.add(two);
                //one.add(three);
            }
            if (click.getSource() == space) {
                in1.setText(in1.getText() + " ");

            }
            if (click.getSource() == clear) {
                int len = in1.getText().length();
                int number = in1.getText().length() - 1;
                String store;
                if (len > 0) {
                    StringBuilder back = new StringBuilder(in1.getText());
                    back.deleteCharAt(number);
                    store = back.toString();
                    in1.setText(store);
                }
            }
            if (click.getSource() == ENTER) {
                result.setText(in1.getText());

            }
        }
    }

    public static void main(String args[]) {


         SwingUtilities.invokeLater(()->new AmharicKeyboard());
        Cc.setVisible(true);
    }
}
