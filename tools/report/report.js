function BodyMain() {
    for (var i = 0; i < 64; i++) {
        var details = document.createElement("details");
        details.open = true;
        details.style.border = "4px double black";
        details.style.background = "#fc3";
        details.style.padding = "10px";
        details.style.marginBottom = "10px";

        var summary = document.createElement("summary");
        var h1 = document.createElement("h1");
        h1.style.display = "inline";
        h1.style.verticalAlign = "middle";
        h1.style.marginLeft = "10px";
        h1.innerHTML = "Click code #" + String(i).padStart(3, '0');
        summary.appendChild(h1);

        var imgClickCode = document.createElement("img");
        imgClickCode.src = String(i).padStart(3, '0') + "-click-code.png";
        imgClickCode.style.display = "inline";
        imgClickCode.style.verticalAlign = "middle";
        imgClickCode.style.marginLeft = "10px";
        summary.appendChild(imgClickCode);

        var divDescription = document.createElement("div");
        divDescription.style.display = "inline";
        imgClickCode.style.verticalAlign = "middle";
        imgClickCode.style.marginLeft = "10px";
        summary.appendChild(divDescription);

        /*
        var xh = new XMLHttpRequest();
        xh.onreadystatechange = function() {
            if (xh.readyState != 4)
                return;

            alert(xh.responseText);
            divDescription.innerHTML = xh.responseText;
        }
        xh.open('GET', String(i).padStart(3, '0') + "-description.txt", true);
        xh.send();
        */

        var div2 = document.createElement("div");

        ["F", "R"].forEach(
            function (dir, index) {
                var par = document.createElement("p");

                var imgGraph = document.createElement("img");
                imgGraph.src = String(i).padStart(3, '0') + dir + "-graph.png";
                par.appendChild(imgGraph);

                var audio = document.createElement("audio");
                audio.controls = true;
                audio.style.width = "100%";

                var audioSource = document.createElement("source");
                audioSource.src = String(i).padStart(3, '0') + dir + "-hamster-sound.wav";
                audioSource.type = "audio/wav";
                audio.appendChild(audioSource);
                par.appendChild(audio);

                div2.appendChild(par)
            }
        )

        details.appendChild(summary);
        details.appendChild(div2)

        document.getElementsByTagName("body")[0].appendChild(details);
    }
}
