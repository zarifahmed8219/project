using Logitech;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

namespace CommunityDoctor
{
    public partial class HoDcRegistration : System.Web.UI.Page
    {
        DataOperation db = new DataOperation();
        protected void Page_Load(object sender, EventArgs e)
        {

        }



        protected void Button1_Click(object sender, EventArgs e)
        {
            string query = @"INSERT INTO [dbo].[HosDoctor]
           ([HO_Code]
           ,[username]
           ,[password]
           ,[Address]
           ,[Phone]
           ,[Email]
           ,[qualification])
     VALUES
           ('" + txthocode.Text + "','" + txtusername.Text + "','" + txtpassword.Text + "','" + txtaddress.Text + "','" + txtphone.Text + "','" + txtemail.Text + "','" + DropDownquali.Text + "' )";
            if (db.executequery(query) == 1)
            {
                Response.Write("<script>alert('Save Successfully!')</script>");
            }
            else
            {
                Response.Write("<script>alert('input error!')</script>");
            }

        }

        protected void Button2_Click(object sender, EventArgs e)
        {
            Response.Redirect("HosDocLogin.aspx");
        }

        protected void Button3_Click(object sender, EventArgs e)
        {
            Response.Redirect("Default.aspx");
        }
    }
}
