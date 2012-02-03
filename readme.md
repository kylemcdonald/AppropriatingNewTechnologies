# Appropriating New Technologies
**Friday 9:30 am to 12:00 pm, Spring 2012**

## Course Description

What do you want your world to look like? This class will focus on creating the future by appropriating new technologies with openFrameworks. openFrameworks is a C++ toolkit designed by a global community of media artists, with an emphasis on real time interaction. Because it's C++, it provides an easy bridge to a huge variety of low level tools like OpenCV and FaceTracker -- which makes it easier to develop otherwise impossible projects, like the EyeWriter, or to explore cutting-edge ideas like real time face substitution. In this class, we'll work with technologies surrounding face tracking, eye tracking, 3d scanning, computer security, privacy, and sharing. We'll spend a lot of time understanding the intricacies of openFrameworks, with the goal of creating seamless, mind-blowing experiments, installations, and performance pieces that hijack new technologies to create the future we want to see. Prerequisites: A deep love for code, an intense passion for democratization of technology, and the ability to geek out when necessary. Or, at least, Introduction to Computational Media. This two-point course will meet in the first seven weeks of the semester.

## Schedule

### Week 1: January 27

#### Agenda

1. Introductions
2. Class overview
3. Assignment preparation: GitHub, code archaeology, distributed creativity

#### Assignment

1. Register for the [openFrameworks forum](http://forum.openframeworks.cc/), and look around to see what people are working on (try [unread posts](http://forum.openframeworks.cc/index.php?action=unread)).
2. If you haven't already, download [openFrameworks](http://www.openframeworks.cc/).
3. Register for [GitHub](https://github.com/). Fork [this repository](https://github.com/kylemcdonald/AppropriatingNewTechnologies) and clone your fork into`openFrameworks/apps/AppropriatingNewTechnologies/`. If you get stuck, GitHub has an excellent [Help](http://help.github.com/) section.
4. Using [CamTwist](http://camtwiststudio.com/download/) and openFrameworks, recreate the idea behind [FaceFlip](http://vimeo.com/10191761) (i.e., capturing a live video stream and sending it back augmented). Zach posted [some code](http://forum.openframeworks.cc/index.php/topic,2946.0.html) to help get you started. You will need to port it to the most recent version of openFrameworks. You are encouraged to collaborate on this portion with other students, merging code from each others' forks. You are not, however, allowed to share files outside of GitHub. If you are using someone else's code, I need to see from the network graph.
5. Augment the video in any way that you think is interesting. Record a video of you testing it on ChatRoulette or elsewhere, and post the video. For this part, you can work by yourself or in a group of exactly two people.
6. After completing the assignment, post a link to your video on the wiki. And the chat logs will also go on the wiki.

### Week 2: February 3

This week we're going to talk about faces.

#### Agenda

1. History of faces and computer vision
2. Haar object detection and OpenCV
3. Active appearance models: [FaceTracker](http://web.mac.com/jsaragih/FaceTracker/FaceTracker.html), [aamlib](https://code.google.com/p/aamlib-opencv/) and [Stasm](http://www.milbo.users.sonic.net/stasm/index.html)

#### Introduction

One of the most salient objects in our day-to-day life is the human face. Faces are so important that the impairment of our face-processing ability is seen as a disorder, called [prosopagnosia](https://en.wikipedia.org/wiki/Prosopagnosia) while unconsciously seeing faces where there are none is an almost universal kind of [pareidolia](https://en.wikipedia.org/wiki/Pareidolia). Without any effort, we maintain a massively multidimensional model that can recognize minor variations in shape and color. One theory says that [color vision evolved in apes to help us empathize](http://www.sciencedaily.com/releases/2006/03/060320221839.htm). Structurally, [Chernoff faces](https://en.wikipedia.org/wiki/Chernoff_faces) use [18 dimensions](http://eagereyes.org/criticism/chernoff-faces) while FACS uses [46 dimensions](https://en.wikipedia.org/wiki/Facial_Action_Coding_System).

When talking about computers vision and faces, there are three major modifiers on the word "face": detection, recognition, and tracking. Each of these has a specific meaning, though they are sometimes used loosely:

1. _Detection_ is a binary classification task. That means it's only about deciding whether something is a face or not. _Detection_ means knowing the difference between a face and a non-face.
2. _Recognition_ is about association, or naming. _Recognition_ means knowing the difference between my face and your face.
3. _Tracking_ is about detection, and possibly recognition, over time. _Tracking_ means knowing that the face in this frame of video is the same as the face in the last frame of video.

When you start talking about properties of the face itself, you will also hear:

1. _Pose_ describes the position and orientation of the face.
2. _Expression_ describes the gesture the face is making.

#### History

> Despite the fact that other methods of identification (such as fingerprints, or iris scans) can be more accurate, face recognition has always remains a major focus of research because of its non-invasive nature and because it is people's primary method of person identification. [Tanzeem Choudhury](http://vismod.media.mit.edu/tech-reports/TR-516/node7.html)

As early as the 1960s, computers were aiding humans with face identification. In 1988/89 researchers developed techniques for automatically recognizing faces if the face was already aligned and normalized. They used techniques like principal components analysis, and neural networks for classification. In 1991 this technique was extended to face detection.

> The technology first captured the public’s attention from the media reaction to a trial implementation at the January 2001 Super Bowl, which captured surveillance images and compared them to a database of digital mugshots. [US Government Subcommittee on Biometrics](www.biometrics.gov/Documents/facerec.pdf)

One of the first databases to offer a baseline for comparing different algorithms was called [The Facial Recognition Technology (FERET) Database](http://www.itl.nist.gov/iad/humanid/feret/feret_master.html). It was developed from 1993-1997 and is still in use today. 

> The goal of the FERET program was to develop automatic face recognition capabilities that could be employed to assist security, intelligence, and law enforcement personnel in the performance of their duties. ... Total funding for the program was in excess of $6.5 million. [NIST](http://www.nist.gov/itl/iad/ig/feret.cfm)

#### Examples

Daito's work: [Electric Stimulus to Face -test3](https://www.youtube.com/watch?v=YxdlYFCp5Ic)

better FACS link
story about making faces at each other all day
[microexpressions](https://en.wikipedia.org/wiki/Microexpression) and [truth wizards](https://en.wikipedia.org/wiki/Wizards_Project)
Perlin's work
[Recognizing Action Units for Facial Expression Analysis](http://www-ee.ccny.cuny.edu/www/web/yltian/Publications/YLBook.pdf) uses feature matching, neural networks, and other techniques to detect interesting features and gestures.
[Change blindness to gradual face changes](http://srsc.ulb.ac.be/axcwww/papers/pdf/06-PB.pdf)
[machine pareidolia](http://urbanhonking.com/ideasfordozens/2012/01/14/machine-pareidolia-hello-little-fella-meets-facetracker/)
even in people with prosopagnosia, skin conductance changes when they see someone familiar

[face morphing, caricatures, and averaging](http://gmeyer3.projects.cs.illinois.edu/cs498dwh/proj4/)
jason salavon's [class of 67/88](http://salavon.com/work/Class/grid/4/)
luke dubois [britney](https://www.youtube.com/watch?v=6QbN8bn3Vno), [play](https://www.youtube.com/watch?v=VzFA11pQIIo) and [a more perfect union](https://www.youtube.com/watch?v=FWq4lk9JYBM&t=1m15s)
[the face of tomorrow](http://www.faceoftomorrow.com/)
[face2face project](http://face2faceproject.com/)
picasa's [face movie](https://www.youtube.com/watch?v=fLQtssJDMMc) requires position, size, rotation

[MPT](http://mplab.ucsd.edu/grants/project1/free-software/mptwebsite/introduction.html)-based smile detection (MPSmile) lead to: theo's [autosmiley](http://fffff.at/auto-smiley/) and theo+me [happy things](http://kylemcdonald.net/happythings/?mode=each)

#### Assignment

1. Decide whether to work with [FaceOSC](https://github.com/kylemcdonald/ofxFaceTracker/downloads), [FaceSubstitution](https://github.com/arturoc/FaceSubstitution), or to detect your own facial gesture. What gesture do you think is most interesting, or most ignored?
2. Make something awesome.

### Week 3: February 10

### Week 4: February 17

### Week 5: February 24

I will be away from class this week. Once it's closer, we can decide whether it makes more sense to reschedule or have someone else lead.

### Week 6: March 2

### Week 7: March 9

## Assignments and Grading

There will be assignments given at the end of the first four weeks, and a final project for the last two weeks.

In order to pass the class, students must complete the assignments, the final project, and attend class. A student will fail if they miss more than one class, miss more than one assignment, or fail to present a completed final project.

## Links

### 3d

[The Kinect Effect](http://www.xbox.com/en-US/Kinect/Kinect-Effect) is a rare case of a product being appropriated, and then re-appropriated by the creators. Also see [Microsoft Bets Big on Kinect for Windows](www.wired.com/epicenter/2012/01/microsoft-bets-kinect-windows/) and [Microsoft Unleashes The Kinect And Promptly Misses The Point](http://www.fastcodesign.com/1665827/microsoft-unleashes-the-kinect-and-promptly-misses-the-point).

![Yo Dawg](http://g.static.memegenerator.net/cache/instances/500x/13/13389/13710965.jpg)

### Computer Vision

[EyeWriter](http://www.eyewriter.org/) uses eye tracking for a novel purposes: enabling graffiti artists. Eye tracking was originally developed to aid Air Force pilots.

Chat Roulette is a unique platform for computer vision-based interactive media and performance. See [FaceFlip](http://vimeo.com/10191761) and [Mario Prank](https://www.youtube.com/watch?feature=player_embedded&v=OTC2I1lHnS4).

[Face Substitution](http://vimeo.com/29348533) and [FaceOSC](http://vimeo.com/26098366) are appropriations of academic face tracking research. The researchers who work on these libraries will sometimes work with defense agencies on surveillance or security applications. [Biometric security](http://www.patentlyapple.com/patently-apple/2011/11/apple-wins-secret-patent-for-high-end-3d-object-recognition.html) is a large related field.

### Crowdsourcing

[Macro Dragnets](http://events.ccc.de/congress/2011/Fahrplan/events/4813.en.html) and [Asking the public to identify criminals](http://bits.blogs.nytimes.com/2011/08/09/london-police-use-flickr-to-identify-looters/).

Amazon Mechanical Turk has been used to create some amazing work. See [Sol Lewitt + Mechanical Turk](http://clementvalla.com/category/work/sol-lewitt-mechanical-turk/) and [A Sequence of...](http://clementvalla.com/category/work/a-sequence-of/) from Clement Valla, as well as [Ten Thousand Cents](http://www.tenthousandcents.com/top.html) and other work from Aaron Koblin.

### Glitch

Glitch art is almost a purely appropriated field. There are [so many good texts](http://gli.tc/h/wiki/index.php/Glitch_theory) I won't list them here. We could spend a whole day just talking about [Jodi](https://en.wikipedia.org/wiki/Jodi#Selected_works) and software appropriation.

### Hacking and Surveillance

[Supervillainizer](http://www.anninaruest.com/a/supervillainizer/index.html) created networks of conspirators to distract intelligence organizations.

The [Metrocard](http://events.ccc.de/congress/2005/fahrplan/events/765.en.html) has been reversed. ITP students have used this to create [MetroChange](http://metrochange.org/).

[L Train Notwork](http://vimeo.com/32149926) provides an unexpected ad-hoc network.

[Newsteek](http://newstweek.com/overview) spoofs an open wifi network and modifies information that goes through it. This is probably illegal.

[OpenPaths](http://openpaths.cc/) was created in response to Apple saving GPS data on the iPhone and transferring it to iTunes without informing users.

[DDoS](https://en.wikipedia.org/wiki/Ddos#Distributed_attack) is a technique that makes it difficult to access a webpage by overloading the server with requests. DDoS attacks are illegal. This type of attack has been used frequently by [Anonymous](http://mashable.com/2010/12/09/how-operation-payback-executes-its-attacks/) in the form of the [LOIC](https://en.wikipedia.org/wiki/LOIC), and by artists for "[virtual sit-ins](http://www.utsandiego.com/news/2010/apr/09/ucsd-prof-turns-meeting-protest-rally/)".

With the right kinds of hardware and time, [WEP](http://lifehacker.com/5305094/how-to-crack-a-wi+fi-networks-wep-password-with-backtrack) and [WPA](http://www.aircrack-ng.org/doku.php?id=cracking_wpa) networks can be cracked. This is illegal.

[Firesheep](https://en.wikipedia.org/wiki/Firesheep) intercepts cookies to steal login data over wireless networks. This is illegal.

[Cross Site Scripting](https://en.wikipedia.org/wiki/Cross-site_scripting) (XSS) can be used to inject content into a remote page using a malformed URL.

[People Staring at Computers](http://vimeo.com/groups/openframeworks/videos/25958231) was a photographic study of computer-mediated interaction that turned into a collaboration with Apple and the Secret Service.

[9/11 Pager data](http://911.wikileaks.org/) was a huge release of all the pager messages throughout the day on 9/11.

### Theory

[Does Hacktivism Matter?](http://events.ccc.de/congress/2011/Fahrplan/events/4749.en.html)

[What is in a name?](http://events.ccc.de/congress/2011/Fahrplan/events/4713.en.html) A historical overview, showing "a name never was ones own but always an intersection of administrative, media-technical and personal interventions".

[Critical Engineering Manifesto](http://criticalengineering.org/) is a short document describing how artists might approach technology critically. It comes from the same people who brought you [Newstweek](http://newstweek.com/overview).

Some of the best artistic appropriation comes from the field of bioart, for which [Critical Art Ensemble](http://www.critical-art.net/) is best known. Particularly relevant is the first chapter of [Electronic Civil Disobedience](http://www.critical-art.net/books/ecd/ecd2.pdf).

### Uncategorized

[Video Toaster](https://www.youtube.com/watch?v=C_K8vnx2ZDc) was like the Kinect in that it brought a previously inaccessible technology to a lower price. The interesting thing is the marketing campaign surrounding it: they were genuinely interested in selling it on the idea of bringing down the large networks.

[US Army uses XBox 360 Controller to fly UAVs](http://www.pyrosoft.co.uk/blog/2007/11/04/army-fly-uav-spy-plane-with-xbox-360-controller/)

[Graffiti Markup Language](http://www.graffitimarkuplanguage.com) (GML) uses XML to describe information that would traditionally not have been described with XML.

[Warhol](https://www.youtube.com/watch?v=3oqUd8utr14) was a master of appropriation, all the way down to the Amiga.

["Avoid ghetto" Bing maps feature](http://news.cnet.com/8301-17852_3-57354445-71/the-joy-of-microsofts-avoid-ghetto-gps-patent/). What kind of routes might you suggest?

[BusTime](http://bustime.mta.info/) from the MTA tells us where a bunch of buses are in NYC.

[Siri](https://github.com/applidium/Cracking-Siri#readme) has been reverse engineered, which means you can use Siri on any device. You can also ask questions and get responses in an automated way.
