﻿using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
/* My using System */
using System.IO;
using System.IO.Ports;
using System.Xml;
using ZedGraph;


namespace Test_GUI_Drawing_Graph
{
    public partial class Form1 : Form
    { 
        double time_start = 0;                            
        const int BUFFER_SIZE = 67;
        byte[] txbuff = new byte[BUFFER_SIZE]; // 1 byte == 8 bit unsigned integer
        /* Transfer data buffer txbuff[] */
        // 0   | 1                  | 2 - 9     | 10 - 17  | 18 - 25   | 26 - 33  | 34 - 41     | 42 - 49   | 50 - 57   | 58 - 65  | 66
        // run | mode_PID, STR, LQR | Setpoint  | Kp       | Ki        | Kd       | Xi          | Omega     | K1        | K2       | type of SetPoint
        /// <Explanation>
        /// - Default: run = 0. If run = 1 then DC Motor starts to run 
        /// - Modes 1, 2, 3: selection for types of controller. 1 for PID, 2 for STR and 3 for LQR
        /// - K_: Kp, Ki, Kd are all double variables [double -- 64 bits -- 8 bytes]
        /// - Xi, Omega_n, K1, K2: double variables [double -- 64 bits -- 8 bytes]
        /// - Type of setpoint: square pulse - 1 or constant value - 0
        /// </summary>

        string strSetPoint, strPocessVar;
        public Form1()
        {
            InitializeComponent();
        }      
        private void comboBox1_SelectedIndexChanged(object sender, EventArgs e)
        {
        }

        private void graph_Init()
        {
            /* Config ZedGraph */
            ///////////////////////////////
            GraphPane mypane = zedGraphControl1.GraphPane; // Khai bao su dung graph loai graphPane
            /* Information for graph */
            mypane.Title.Text = "Response Graph";
            mypane.XAxis.Title.Text = "Time (s)";
            mypane.YAxis.Title.Text = "Value";

            /* Dinh nghia list de ve do thi voi 60000 points */
            RollingPointPairList list1 = new RollingPointPairList(60000);
            RollingPointPairList list2 = new RollingPointPairList(60000);

            // Dinh nghia Curve de ve do thi
            LineItem curve1 = mypane.AddCurve("Set Point", list1, Color.Red, SymbolType.None); //Auto draw
            LineItem curve2 = mypane.AddCurve("Process Variables", list2, Color.Blue, SymbolType.None); //Auto draw

            mypane.XAxis.Scale.Min = 0;
            mypane.XAxis.Scale.Max = 10;
            mypane.XAxis.Scale.MinorStep = 0.1; // Don vi chia nho nhat la 1
            mypane.XAxis.Scale.MajorStep = 1;
            mypane.YAxis.Scale.Min = -10;
            mypane.YAxis.Scale.Max = 1000;
            mypane.YAxis.Scale.MajorStep = 100;
            mypane.AxisChange();// Goi ham xac dinh cowx trujc
            ////////////////////////////////
        }
        private void btConnect_Click(object sender, EventArgs e)
        {
            if (!serialPort.IsOpen)
            {
                serialPort.Open();     
            }
            if(serialPort.IsOpen)
            {
                btExit.Enabled = true;
                label1.Text = "Connecting";
                label1.ForeColor = Color.Green;
                lbBaud.Text = "Baudrate: 115200";
            }
        }

        private void btExit_Click(object sender, EventArgs e)
        {
            DialogResult answer;
            answer = MessageBox.Show("Are you sure to be out", "Exit", MessageBoxButtons.OKCancel, MessageBoxIcon.Warning);
            if(answer==DialogResult.OK)
            {
                serialPort.Close();
                Application.Exit();
            }        
        }

        private void btRun_Click(object sender, EventArgs e)
        {
            if (serialPort.IsOpen)
            {
                txbuff[0] = 1;
                label1.Text = "DC motor is set to run";
                label1.ForeColor = Color.DarkOrange;
                btRun.Enabled = false;
                resetGraph();
                timer1.Enabled = true;               
            }
            else MessageBox.Show("Can't connect to the device", "Error", MessageBoxButtons.RetryCancel, MessageBoxIcon.Warning);
        }

        private void btClear_Click(object sender, EventArgs e)
        {
            btRun.Enabled = true;
            btnSquarePulse.Enabled = true;
            txbuff[66] = 0; // Set default Setpoint type to constant value
            if (serialPort.IsOpen)
            {
                txbuff[0] = 0;
                //btRun.Enabled = true;

                btnPID.Enabled = true;
                btnPID.ForeColor = Color.Black;
                btnLQR.Enabled = true;
                btnLQR.ForeColor = Color.Black;
                btnSTR.Enabled = true;
                btnSTR.ForeColor = Color.Black;

                txtKp.Text = "0";
                txtKi.Text = "0";
                txtKd.Text = "0";
                txtXi.Text = "0";
                txtOmegan.Text = "0";            
                txtK1.Text = "0";
                txtK2.Text = "0";
                txtSp.Text = "0";

                /*--------- Setpoint ---------*/
                byte[] setPoint = new byte[8];
                byte[] tmpSP = Encoding.ASCII.GetBytes(txtSp.Text);
                for (int i = 0; i < tmpSP.Length; i++)
                    setPoint[i] = tmpSP[i];
                Array.Copy(setPoint, 0, txbuff, 2, 8);

                dProcessVar = 0;
                txtPv.Text = dProcessVar.ToString();

                /*--------- Kp ---------*/
                byte[] kp = new byte[8];
                byte[] tmpKP = Encoding.ASCII.GetBytes(txtKp.Text);
                for (int i = 0; i < tmpKP.Length; i++)
                    kp[i] = tmpKP[i];
                Array.Copy(kp, 0, txbuff, 10, 8);

                /*--------- Ki ---------*/
                byte[] ki = new byte[8];
                byte[] tmpKI = Encoding.ASCII.GetBytes(txtKi.Text);
                for (int i = 0; i < tmpKI.Length; i++)
                    ki[i] = tmpKI[i];
                Array.Copy(ki, 0, txbuff, 18, 8);

                /*--------- Kd ---------*/
                byte[] kd = new byte[8];
                byte[] tmpKD = Encoding.ASCII.GetBytes(txtKd.Text);
                for (int i = 0; i < tmpKD.Length; i++)
                    kd[i] = tmpKD[i];
                Array.Copy(kd, 0, txbuff, 26, 8);               

                /*--------- Xi ---------*/
                byte[] xi = new byte[8];
                byte[] tmpXI = Encoding.ASCII.GetBytes(txtXi.Text);
                for (int i = 0; i < tmpXI.Length; i++)
                    xi[i] = tmpXI[i];
                Array.Copy(xi, 0, txbuff, 34, 8);

                /*--------- Omega_n ---------*/
                byte[] omegaN = new byte[8];
                byte[] tmpOMEGA = Encoding.ASCII.GetBytes(txtOmegan.Text);
                for (int i = 0; i < tmpOMEGA.Length; i++)
                    omegaN[i] = tmpOMEGA[i];
                Array.Copy(omegaN, 0, txbuff, 42, 8);

                /*--------- K1 ---------*/
                byte[] k1 = new byte[8];
                byte[] tmpK1 = Encoding.ASCII.GetBytes(txtK1.Text);
                for (int i = 0; i < tmpK1.Length; i++)
                    k1[i] = tmpK1[i];
                Array.Copy(k1, 0, txbuff, 50, 8);

                /*--------- K2 ---------*/
                byte[] k2 = new byte[8];
                byte[] tmpK2 = Encoding.ASCII.GetBytes(txtK2.Text);
                for (int i = 0; i < tmpK2.Length; i++)
                    k2[i] = tmpK2[i];
                Array.Copy(k2, 0, txbuff, 58, 8);

                /* REMEMBER TO SEND DATA */
                serialPort.Write(txbuff, 0, BUFFER_SIZE);

                label1.Text = "All the data has been cleared";
                label1.ForeColor = Color.YellowGreen;

                //dProcessVar = 0;
                //txtPv.Text = dProcessVar.ToString();
                //dSetPoint = 0;
                //txtSp.Text = dSetPoint.ToString();
                resetGraph();                  
            }
        }

        private void progressBar1_Click(object sender, EventArgs e)
        {

        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            if (!serialPort.IsOpen)
            {
                progressBar1.Value = 0;
            }
            else if (serialPort.IsOpen) 
            {
                progressBar1.Value = 100;
                draw(strSetPoint, strPocessVar);                
            }
        }
        private void labelStatus_Click (object sender, EventArgs e)
        {

        }
        private void zedGraphControl1_Load(object sender, EventArgs e)
        {            
        }

        double dSetPoint, dProcessVar;
        private void draw(string setPoint, string processVar)
        {
            /*
             * Converts the string representation of a number to its double-precision floating-point number equivalent. 
             * A return value indicates whether the conversion succeeded or failed.  
             * Reference: https://docs.microsoft.com/en-us/dotnet/api/system.double.tryparse?view=net-6.0
             */
            double.TryParse(setPoint, out dSetPoint);
            double.TryParse(processVar, out dProcessVar);
            //if (dProcessVar == 0) return;     // Not showing process variables that equal to zero
            if (zedGraphControl1.GraphPane.CurveList.Count <= 0) return; // Kiem tra viec khoi tao cac duong curve

            /*Dua ve diem xuat phat*/
            LineItem curve1 = zedGraphControl1.GraphPane.CurveList[0] as LineItem;   //Khai bao duong cong duoc ke thua tu duong cong khoi tao trong ham graph_Init()
            LineItem curve2 = zedGraphControl1.GraphPane.CurveList[1] as LineItem;
            if (curve1 == null) return;
            if (curve2 == null) return;

            /*List chua cac diem tren duong cong cua do thi ___Get the pointpair list */
            IPointListEdit list1 = curve1.Points as IPointListEdit;
            IPointListEdit list2 = curve2.Points as IPointListEdit;
            if (list1 == null) return;
            if (list2 == null) return;

            //LineItem curve = mypane.AddCurve("Data", list1, Color.Red, SymbolType.None);   // Draw curve

            double real_time = (Environment.TickCount - time_start)/1000.0;            
            list1.Add(real_time, dSetPoint);     // Ham hien thi du lieu Set Point tren do thi 
            list2.Add(real_time, dProcessVar);   // Ham hien thi du lieu Process Variables tren do thi 

            /* Doan chuong trinh thuc hien ve do thi */
            Scale xAxisScale = zedGraphControl1.GraphPane.XAxis.Scale;
            Scale yAxisScale = zedGraphControl1.GraphPane.YAxis.Scale;

            // Tu dong scale theo truc X
            if(real_time > xAxisScale.Max - xAxisScale.MajorStep)
            {
                xAxisScale.Max = real_time + xAxisScale.MajorStep;

                /* Thoi gian chay qua 40s se tu dong tinh tien sang trai.
                Neu khong muon dich chuyen ma bat dau tu 0 thi de xAxisScale.Min=0 */
                xAxisScale.Min = 0;
                    //xAxisScale.Max - 40; 
            }

            // Tu dong scale theo truc y
            if(dSetPoint > yAxisScale.Max-yAxisScale.MajorStep)
            {
                yAxisScale.Max = dSetPoint + yAxisScale.MajorStep;
            }
            else if(dSetPoint < yAxisScale.Min-yAxisScale.MajorStep)
            {
                yAxisScale.Min = dSetPoint - yAxisScale.MajorStep;
            }

            zedGraphControl1.AxisChange();  // Ve do thi
            zedGraphControl1.Invalidate();  // Force a red draw, mo khoa de ve lai
            zedGraphControl1.Refresh();

            txtPv.Text = dProcessVar.ToString();            
        }

        private void resetGraph()
        {
            // Voi zedgraph, khi xoa di thi phai khai bao lai, neu khong se khong hien thi do thi
            zedGraphControl1.GraphPane.CurveList.Clear();       // Xoa moi duong cong
            zedGraphControl1.GraphPane.GraphObjList.Clear();    // xoa moi doi tuong 
            zedGraphControl1.Invalidate();
            //zedGraphControl1.AxisChange();

            // khai bao lai...         
            graph_Init();            
            time_start = Environment.TickCount;

        }

        private void Form1_Load_1(object sender, EventArgs e)
        {
            comboBox1.DataSource = SerialPort.GetPortNames(); // Scan cac cong COM khi mo chuong trinh   
            graph_Init();
            time_start = Environment.TickCount;         // THIS IS THE FUCKING BUG
        }         
        private void label1_Click (object sender, EventArgs e) { }
        private void label2_Click(object sender, EventArgs e) { }
        string data;
        private void SerialDataReceived(object sender, SerialDataReceivedEventArgs e)
        {
            if (serialPort.IsOpen)
            {
                data = "";
                data = serialPort.ReadLine();
                serialPort.DiscardInBuffer();
                string[] dataList = data.Split(',');
                if (dataList.Length < 3) return;                
                    if (dataList[0] == "S")
                    {
                        strSetPoint = dataList[1];
                        strPocessVar = dataList[2];
                    }                              
            }
        }
        private void btnPID_Click(object sender, EventArgs e)
        {
            btnLQR.Enabled = false;
            btnSTR.Enabled = false;
            btnPID.ForeColor = Color.Green;

            //txbuff[0] = 1;
            txbuff[1] = 1;  // Mode selection PID            
            /*--------- Kp ---------*/
            byte[] kp = new byte[8];
            byte[] tmpKP = Encoding.ASCII.GetBytes(txtKp.Text);
            for (int i = 0; i < tmpKP.Length; i++)
                kp[i] = tmpKP[i];
            Array.Copy(kp, 0, txbuff, 10, 8);

            /*--------- Ki ---------*/
            byte[] ki = new byte[8];
            byte[] tmpKI = Encoding.ASCII.GetBytes(txtKi.Text);
            for (int i = 0; i < tmpKI.Length; i++)
                ki[i] = tmpKI[i];
            Array.Copy(ki, 0, txbuff, 18, 8);

            /*--------- Kd ---------*/
            byte[] kd = new byte[8];
            byte[] tmpKD = Encoding.ASCII.GetBytes(txtKd.Text);
            for (int i = 0; i < tmpKD.Length; i++)
                kd[i] = tmpKD[i];
            Array.Copy(kd, 0, txbuff, 26, 8);           
        }

        private void btnSTR_Click(object sender, EventArgs e)
        {
            btnPID.Enabled = false;
            btnLQR.Enabled = false;
            btnSTR.ForeColor = Color.Green;

            //txbuff[0] = 1;
            txbuff[1] = 2;  // Mode selection LQR 
            /*--------- Xi ---------*/
            byte[] xi = new byte[8];
            byte[] tmpXI = Encoding.ASCII.GetBytes(txtXi.Text);
            for (int i = 0; i < tmpXI.Length; i++)
                xi[i] = tmpXI[i];
            Array.Copy(xi, 0, txbuff, 34, 8);

            /*--------- Omega_n ---------*/
            byte[] omegaN = new byte[8];
            byte[] tmpOMEGA = Encoding.ASCII.GetBytes(txtOmegan.Text);
            for (int i = 0; i < tmpOMEGA.Length; i++)
                omegaN[i] = tmpOMEGA[i];
            Array.Copy(omegaN, 0, txbuff, 42, 8);
        }

        private void btnLQR_Click(object sender, EventArgs e)
        {
            btnPID.Enabled = false;
            btnSTR.Enabled = false;
            btnLQR.ForeColor = Color.Green;

            //txbuff[0] = 1;
            txbuff[1] = 3;  // Mode selection LQR 
            /*--------- K1 ---------*/
            byte[] k1 = new byte[8];
            byte[] tmpK1 = Encoding.ASCII.GetBytes(txtK1.Text);
            for (int i = 0; i < tmpK1.Length; i++)
                k1[i] = tmpK1[i];
            Array.Copy(k1, 0, txbuff, 50, 8);

            /*--------- K2 ---------*/
            byte[] k2 = new byte[8];
            byte[] tmpK2 = Encoding.ASCII.GetBytes(txtK2.Text);
            for (int i = 0; i < tmpK2.Length; i++)
                k2[i] = tmpK2[i];
            Array.Copy(k2, 0, txbuff, 58, 8);

        }

        private void btnSend_Click(object sender, EventArgs e)
        {
            serialPort.Write(txbuff, 0, BUFFER_SIZE);
            label1.Text = "Drawing";
            label1.ForeColor = Color.Teal;

        }

        private void btnSquarePulse_Click(object sender, EventArgs e)
        {
            txbuff[66] = 1;
            btnSquarePulse.Enabled = false;
        }

        private void btnStop_Click(object sender, EventArgs e)
        {
            btRun.Enabled = true;
            txbuff[0] = 0;
            txbuff[66] = 0; // Set default Setpoint type to constant value
            serialPort.Write(txbuff, 0, BUFFER_SIZE);
            timer1.Enabled = false;
            label1.Text = "Stop drawing";
            label1.ForeColor = Color.YellowGreen;
        }

        private void btnOK_Click(object sender, EventArgs e)
        {
            /* Transfer Setpoint value to STM32 */
            /*
             First, we need to declare 8 bytes for Setpoint values, cause we are going to transfer an 8-byte double value in string form
                from GUI to STM. But the code Encoding.ASCII.GetBytes() does not always return 8 bytes, so we need the below for-loop. 
                    The rest elements of setPoint gets values of 0. 
                        Finally, we copy setPoint string to Tx_buffer frame.             
             */
            byte[] setPoint = new byte[8];
            byte[] tmpSP = Encoding.ASCII.GetBytes(txtSp.Text);
            for (int i = 0; i < tmpSP.Length; i++)
                setPoint[i] = tmpSP[i];
            //Encoding.ASCII.GetBytes(txtSp.Text);
            //BitConverter.GetBytes(Int16.Parse(txtSp.Text));
            Array.Copy(setPoint, 0, txbuff, 2, 8);

            label1.Text = "The data is ready to be transferred";
            label1.ForeColor = Color.Red;
        }
    }
}
