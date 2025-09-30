[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/1PRAkQnI)
# Identity
Name : Nazwa Aiana Putri (1313623016)

# AI usage
Explain how you use the AI to solve the assignment. Put all ***your used queries*** in this section & what kind of AI are you using. Declare not using AI if you didn't do this.  
- Saya menggunakan bantuan AI di beberapa bagian saat mengerjakan tugas ini. Pertama, saya sempat mengalami kendala ketika project tidak bisa dijalankan karena muncul error CMake project configuration failed. Untuk masalah itu saya bertanya ke ChatGPT supaya project bisa dijalankan dengan benar. Kedua, saya juga menggunakan AI Gemini untuk memahami bagian algoritma Fast Convex Hull, karena saya bingung dengan logikanya terutama di bagian yang mengatur upper hull dan lower hull. Selain itu, saya juga menanyakan tentang algoritma Slow Convex Hull, khususnya pada bagian kode yang mengecek semua pasangan titik (i, j) dan menentukan kandidat hull dengan variabel allRightOrCollinear.

Query yang saya pakai sebagai berikut:
- Slow Convex Hull
```
QSet<QPoint> hullCandidates;
for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
        if (i == j) continue;

        bool allRightOrCollinear = true;

        for (int k = 0; k < n; k++) {
            if (k == i || k == j) continue;
            m_iterations++;

            int orient = orientation(points[i], points[j], points[k]);

            if (orient == 2) {
                allRightOrCollinear = false;
                break;
            }
        }

        if (allRightOrCollinear) {
            hullCandidates.insert(points[i]);
            hullCandidates.insert(points[j]);
        }
    }
}
```

- Fast Convex HUll
```
 QVector<QPoint> upperHull;
    for (int i = 0; i < final_n; ++i) {
        m_iterations++;
        while (upperHull.size() >= 2 && orientation(upperHull[upperHull.size()-2], upperHull.last(), P[i]) != 2)
        {
            m_iterations++;
            upperHull.pop_back();
        }
        upperHull.push_back(P[i]);
    }

    QVector<QPoint> lowerHull;
    for (int i = final_n - 1; i >= 0; --i) {
        m_iterations++;
        while (lowerHull.size() >= 2 && orientation(lowerHull[lowerHull.size()-2], lowerHull.last(), P[i]) != 2)
        {
            m_iterations++;
            lowerHull.pop_back();
        }
        lowerHull.push_back(P[i]);
    }
```

# Collaboration usage
Explain how you are ***using others*** to complete the assignment in this section. Are they simply copying, learn the ideas, learn how to adapt the AI or anything involving the process. State the people if any & Please be elaborate. Declare self tought if you solved this by yourself. 
- Saya mengerjakan tugas ini bersama dengan Khalisa Rajwa Nazira. Kami berdiskusi tentang bagaimana cara mengimplementasikan kedua algoritma tersebut. Awalnya kami sempat bingung, apakah sebaiknya dibuat satu tombol untuk langsung menjalankan dua algoritma sekaligus, atau lebih baik menggunakan dua tombol terpisah untuk masing-masing algoritma. Setelah berdiskusi, akhirnya kami bisa menentukan cara yang lebih jelas untuk dipakai di program.

# Commit Rules
Use .gitignore to stripe any binaries from the resulting build before commit.  If you cloned directly from the template, you are safe. 

# Due Time
September 30th, 2025. 23: 59 WIB
