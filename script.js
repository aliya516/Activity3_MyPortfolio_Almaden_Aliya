/* Set the width of the sidebar to 250px (show it) */
/*function openNav() {
    document.getElementById("mySidepanel").style.width = "230px";
  }*/

  /*  function openNav() {
        const panel = document.getElementById("mySidepanel");
        panel.style.width = "230px";
        panel.style.height = "1000px"; // Adjusted property
    }*/
  
/*function openNav(){
    document.getElementById("mySidepanel").style.length = "100px";
}*/
  /* Set the width of the sidebar to 0 (hide it) */
  /*function closeNav() {
    document.getElementById("mySidepanel").style.width = "0";
  }*/
    function openNav() {
        document.getElementById("mySidepanel").style.width = "250px";
        document.querySelector(".openbtn").style.visibility = "hidden";
        document.querySelector(".closebtn").style.visibility = "visible";
    }
    
    function closeNav() {
        document.getElementById("mySidepanel").style.width = "0";
        document.querySelector(".openbtn").style.visibility = "visible";
        document.querySelector(".closebtn").style.visibility = "hidden";
    }
    

