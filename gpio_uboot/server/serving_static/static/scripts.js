let url = 'http://127.0.0.1:5000/files';

fetch(url)
.then(res => res.json())
.then((out) => {
  console.log('FILESLIST! ', out);
  out.forEach(element => {
    var node = document.createElement("LI");                 // Create a <li> node
    var link = document.createElement("a");
    var linkText = document.createTextNode(element);
    link.appendChild(linkText);
    link.title = element;
    link.href = "files/" + element;  
    node.appendChild(link);                              // Append the text to <li>
    document.getElementById("list").appendChild(node);     // Append <li> to <ul> with id="myList" 
  });
})
.catch(err => { throw err });



let button = document.createElement("button");
button.setAttribute("style", "font-size: 3em;");
let label = document.createElement("label");
label.setAttribute("for", "inputId");
label.setAttribute("style", "border-radius: 15%;");
let labelText = document.createTextNode("UPLOAD FILE");
label.appendChild(labelText);
let input2 = document.createElement("input");
input2.setAttribute("id", "inputId");
input2.setAttribute("type", "file");
input2.setAttribute("style", "position: fixed; top: -100em");
button.appendChild(label);
button.appendChild(input2);
console.log(button);
document.getElementById("but").appendChild(button);

let input = document.getElementById("inputId");
input.onchange = e => { 

  // getting a hold of the file reference
  var file = e.target.files[0]; 

  // setting up the reader
  let formData = new FormData();
  formData.append("file", file);
  path = "files/" + file.name;
  fetch(path, {method: "POST", body: formData})
  .then((out) => location.reload());
}