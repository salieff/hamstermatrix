function BodyMain() {
    for (let i = 0; i < 64; i++) {
        let details = document.createElement("details");
        details.open = true;
        details.style.border = "4px double black";
        details.style.background = "#fc3";
        details.style.padding = "10px";
        details.style.marginBottom = "10px";

        let summary = document.createElement("summary");

        let h1 = document.createElement("h1");
        h1.style.display = "inline";
        h1.style.verticalAlign = "middle";
        h1.style.marginLeft = "10px";
        h1.innerHTML = "Click code #" + String(i).padStart(3, '0');
        summary.appendChild(h1);

        let imgClickCode = document.createElement("img");
        imgClickCode.src = String(i).padStart(3, '0') + "-click-code.png";
        imgClickCode.style.display = "inline";
        imgClickCode.style.verticalAlign = "middle";
        imgClickCode.style.marginLeft = "10px";
        summary.appendChild(imgClickCode);

        let divDescription = document.createElement("div");
        divDescription.style.display = "inline";
        divDescription.style.verticalAlign = "middle";
        divDescription.style.marginLeft = "10px";
        if (DescriptionMap.has(i))
        {
            divDescription.innerHTML = DescriptionMap.get(i);
        }
        else
        {
            details.style.background = "#00cccc";
            details.open = false;
        }
        summary.appendChild(divDescription);

        let div2 = document.createElement("div");

        ["F", "R"].forEach(
            function (dir, index) {
                let par = document.createElement("p");

                let imgGraph = document.createElement("img");
                imgGraph.src = String(i).padStart(3, '0') + dir + "-graph.png";
                imgGraph.onerror = function() { details.style.background = "#00cccc"; details.open = false; }
                par.appendChild(imgGraph);

                let audio = document.createElement("audio");
                audio.controls = true;
                audio.style.width = "100%";

                let audioSource = document.createElement("source");
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
